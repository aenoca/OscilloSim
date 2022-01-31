#include "../Oscillators/constants.h"
#include "../Oscillators/oscillator.h"
#include "../Oscillators/weightedpendulum.h"
#include "../Oscillators/spring.h"
#include "../Oscillators/doublependulum.h"
#include "../Oscillators/springpendulum.h"
#include <cmath>
#include "view_opengl.h"
#include "vertex_shader.h" // Identifiants Qt de nos différents attributs
#include "../Simulation/system.h"

void ViewOpenGL::init()
{
  /* Initialise notre vue OpenGL.
   * Dans cet exemple, nous créons et activons notre shader.
   *
   * En raison du contenu des fichiers *.glsl, le shader de cet exemple
   * NE permet QUE de dessiner des primitives colorées 
   * (pas de textures, brouillard, reflets de la lumière ou autres).
   *
   * Il est séparé en deux parties VERTEX et FRAGMENT.
   * Le VERTEX :
   * - récupère pour chaque sommet des primitives de couleur (dans
   *     l'attribut couleur) et de position (dans l'attribut sommet)
   * - multiplie l'attribut sommet par les matrices 'vue_modele' et
   *     'projection' et donne le résultat à OpenGL
   *   - passe la couleur au shader FRAGMENT.
   *
   * Le FRAGMENT :
   *   - applique la couleur qu'on lui donne
   */

  prog.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/vertex_shader.glsl");
  prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");

  /* Identifie les deux attributs du shader de cet exemple
   * (voir vertex_shader.glsl).
   *
   * L'attribut identifié par 0 est particulier, il permet d'envoyer un
   * nouveau "point" à OpenGL
   * 
   * C'est pourquoi il devra obligatoirement être spécifié et en dernier 
   * (après la couleur dans cet exemple, voir plus bas).
   */

  prog.bindAttributeLocation("sommet",  SommetId);
  prog.bindAttributeLocation("couleur", CouleurId);
  
  // Compilation du shader OpenGL
  prog.link();

  // Activation du shader
  prog.bind();

  /* Activation du "Test de profondeur" et du "Back-face culling"
   * Le Test de profondeur permet de dessiner un objet à l'arrière-plan
   * partielement caché par d'autres objets.
   * 
   * Le Back-face culling consiste à ne dessiner que les face avec ordre 
   * de déclaration dans le sens trigonométrique.
   */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  glLineWidth(5); // modification de la largeur des lignes

  initializePosition();
}

// ======================================================================
void ViewOpenGL::initializePosition()
{
  // position initiale
  matrix_view.setToIdentity();
  matrix_view.rotate(90, 0, 1, 0);
  matrix_view.translate(4.0, 0.0, 0.0);


  matrix_view.rotate(-90, 1.0, 0.0, 0.0);
  matrix_view.rotate(90, 0.0, 0, 1.0);
  matrix_view.rotate(75, 0, 0, 1);
  matrix_view.translate(0.0, 0.0, -1);
  matrix_view.translate(-2.0, 0.0, 0.0);
}

// ======================================================================
void ViewOpenGL::translate(double x, double y, double z)
{
  /* Multiplie la matrice de vue par LA GAUCHE.
   * Cela fait en sorte que la dernière modification apportée
   * à la matrice soit appliquée en dernier (composition de fonctions).
   */
  QMatrix4x4 supp_trans;
  supp_trans.translate(x, y, z);
  matrix_view = supp_trans * matrix_view;
}

// ======================================================================
void ViewOpenGL::rotate(double angle, double dir_x, double dir_y, double dir_z)
{
  // Multiplie la matrice de vue par LA GAUCHE
  QMatrix4x4 supp_rot;
  supp_rot.rotate(angle, dir_x, dir_y, dir_z);
  matrix_view = supp_rot * matrix_view;
}

// ======================================================================

void ViewOpenGL::drawAxes (QMatrix4x4 const& viewpoint, bool in_color)
{
  prog.setUniformValue("vue_modele", matrix_view * viewpoint);

  glLineWidth(3);
  glBegin(GL_LINES); //La directive GL_lines permet de dessiner uniquement des segments

  // axe X
  if (in_color) {
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
  } else {
    prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0); // blanc
  }
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 1.0, 0.0, 0.0);

  // axe Y
  if (in_color) prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // vert
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 0.0, 1.0, 0.0);

  // axe Z
  if (in_color) prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // bleu
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 0.0, 0.0, 1.0);

  glEnd();
}

void ViewOpenGL::drawGrid()
{
    /* On boucle deux fois pour creer des segments parallèles
     * puis les segments perpendiculaires
     */
    prog.setUniformValue("vue_modele", matrix_view);
    glLineWidth(0.5);
    glBegin(GL_LINES);
    prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0);

    for(double i(-5); i <=5; i+= 0.5){
        prog.setAttributeValue(SommetId, i, -5.0, 0.0);
        prog.setAttributeValue(SommetId, i, 5.0, 0.0);
    }

    for(double j(-5); j <=5; j+=0.5){
        prog.setAttributeValue(SommetId, -5.0, j, 0.0);
        prog.setAttributeValue(SommetId, 5.0, j, 0.0);
    }
    glEnd();

}

void ViewOpenGL::drawSphere (QMatrix4x4 const& viewpoint, GLSphere s, double red, double green, double blue)
{
      prog.setUniformValue("vue_modele", matrix_view * viewpoint);
      prog.setAttributeValue(CouleurId, red, green, blue);  // met la couleur
      s.draw(prog, SommetId);                           // dessine la sphère
}

void ViewOpenGL::drawSpring2D(Vector const& o, Vector const& P, Vector const& perp)
{
    // o. P et perp sont tous les trois de dimension 3
    //Cette méthode permet de créer la forme tant caractéristique d'un ressort
    //Elle recoit en paramètre l'origine, la direction (axe de l'oscillateur)
    //et un Vector perpendiculaire à l'axe
    double delt = 0.1;
    Vector delta = delt * perp;

    double n = 10; //nb de points

    prog.setUniformValue("vue_modele", matrix_view);
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0);
    glLineWidth(5);
    glBegin(GL_LINE_STRIP);
    /*
     * On  a n+4 points : 2 par extémité et n points
     * intermédiaires. On crée tout d'abord des segments
     * droits (dans le direction de P) aux extrémités, puis on commence les zigs-zags.
     * Pour ces derniers, on utilise le Vector perpendiculaire
     * pour périodiquement créer des points alternés éloignés de
     * l'axe du pendule
     */

    //Premier point
    prog.setAttributeValue(SommetId, o[1], o[2], o[3]);

    //Deuxième point
    Vector eps1 = o + 1/(n+4) * P; //Problème ici
    prog.setAttributeValue(SommetId, eps1[1], eps1[2], eps1[3]);

    //n points entre deux
    for(size_t i(2); i <= n + 2; ++i)
    {
        Vector temp = o + i/(n+4) * P;
        if(i % 2 == 0) temp += delta;
        else temp -= delta;
        prog.setAttributeValue(SommetId, temp[1], temp[2], temp[3]);
    }

    //Avant dernier point
    Vector epsn = o + (n+3)/(n+4) * P;
    prog.setAttributeValue(SommetId, epsn[1],epsn[2], epsn[3]);

    //Dernier point
    Vector last = o + P;
    prog.setAttributeValue(SommetId, last[1],last[2], last[3]);
    glEnd();
}

void ViewOpenGL::drawSpring3D(Vector const& o, Vector const& P, Vector const& perp)
{
    // o. P et perp sont tous les trois de dimension 3
    //Cette méthode permet de créer la forme tant caractéristique d'un ressort
    //Elle recoit en paramètre l'origine, la direction (axe de l'oscillateur)
    //et un Vector perpendiculaire à l'axe

    double delt = 0.1;
    Vector delta = delt * perp;

    double boucle(10.0);    //le nombre de boucle du ressort
    size_t n(1000);             //le nombres de points

    double r(0.1);          //rayon de l'helice


    prog.setUniformValue("vue_modele", matrix_view);
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0);
    glLineWidth(5);
    glBegin(GL_LINE_STRIP);
    /*
     * On  a n+4 points : 2 par extémité et n points
     */

    //Premier point
    prog.setAttributeValue(SommetId, o[1], o[2], o[3]);

    //Deuxième point
    Vector eps1 = o + 1/(n+4) * P;
    prog.setAttributeValue(SommetId, eps1[1], eps1[2], eps1[3]);

    //n points entre deux
    for(size_t i(2); i <= n + 2; ++i) //mis a n+2 au lieu de n+3
    {

        double nb(n);
        double ti(i/nb);

        Vector vec1(r * cos(boucle * 2 * M_PI * ti) * (perp.unit() ^ P.unit()) );
        Vector vec2(r * sin(boucle * 2 * M_PI * ti) * perp.unit());
        Vector vec3(ti * P);

        double x(o[1] + vec1[1]+vec2[1]+vec3[1]);
        double y(o[2] + vec1[2]+vec2[2]+vec3[2]);
        double z(o[3] + vec1[3]+vec2[3]+vec3[3]);

        prog.setAttributeValue(SommetId, x, y, z);
    }

    //Avant dernier point

    //Vector epsn = o + (n+3)/(n+4) * P;
    //prog.setAttributeValue(SommetId, epsn[1],epsn[2], epsn[3]);
    //Dernier point
    Vector last = o + P;
    prog.setAttributeValue(SommetId, last[1],last[2], last[3]);
    glEnd();
}

// ======================================================================

void ViewOpenGL::draw(System const& s)
{
    s.drawSystem();
    drawAxes();
    drawGrid();
}

// ======================================================================

void ViewOpenGL::draw(WeightedPendulum const& p)
{
    Vector A = Vector({p.getA()[1], p.getA()[2], 0}).unit();
    Vector v = p.getO() + p.getL() * cos(p.getP()[1])*(1.0/g_CONST) * G_CONST + p.getL() * sin(p.getP()[1]) * A;

    prog.setUniformValue("vue_modele", matrix_view);
    glLineWidth(5);
    glBegin(GL_LINES);
    //Couleur
    prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0);
    //Position fixe O
    prog.setAttributeValue(SommetId, p.getO()[1], p.getO()[2], p.getO()[3]);

    prog.setAttributeValue(SommetId, v[1], v[2], v[3]);
    glEnd();

    //Dessin de la sphère
    GLSphere sphere1;
    sphere1.initialize();

    QMatrix4x4 Pos_1;
    Pos_1.translate(v[1], v[2], v[3]);
    Pos_1.scale(0.1);
    drawSphere(Pos_1, sphere1, 0, 0, 1);
}

// ======================================================================

void ViewOpenGL::draw(DoublePendulum const& dp)
{
    //Vectors positions
    Vector A = Vector({dp.getA()[1], dp.getA()[2], 0}).unit();

    Vector v = dp.getO() + dp.getL() * cos(dp.getP()[1]) * (1/G_CONST.norm()) * G_CONST +
                dp.getL() * sin(dp.getP()[1]) * A;

    Vector v2 = v + dp.getL2() * cos(dp.getP()[2]) * (1/G_CONST.norm()) * G_CONST +
                     dp.getL2() * sin(dp.getP()[2]) * A;

    prog.setUniformValue("vue_modele", matrix_view);
    glLineWidth(5);
    glBegin(GL_LINES);

    //Couleur
    prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0);

    //Position centre 1
    prog.setAttributeValue(SommetId, dp.getO()[1], dp.getO()[2], dp.getO()[3]);
    //Position masse 1
    prog.setAttributeValue(SommetId, v[1], v[2], v[3]);

    //Deuxième segment
    //Couleur
    prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0);
    //Position O de l'autre
    //prog.setUniformValue("vue_modele", matrix_view);

    //Position centre 2
    prog.setAttributeValue(SommetId, v[1], v[2], v[3]);
    //Position masse 2
    prog.setAttributeValue(SommetId, v2[1], v2[2], v2[3]);
    glEnd();

    //Dessin des 2 sphères
    GLSphere sphere1;
    GLSphere sphere2;
    sphere1.initialize();
    sphere2.initialize();

    QMatrix4x4 Pos_1;
    QMatrix4x4 Pos_2;
    Pos_1.translate(v[1], v[2], v[3]);
    Pos_1.scale(0.1);
    Pos_2.translate(v2[1], v2[2], v2[3]);
    Pos_2.scale(0.1);
    drawSphere(Pos_1, sphere1);
    drawSphere(Pos_2, sphere2);
}

// ======================================================================

void ViewOpenGL::draw(Spring const& r)
{
    ///////////////////////////////Problème avec desswine ressort 3D
    //Vector position
    Vector axe = r.getP()[1] * r.getA();
    Vector v = r.getO() + axe;

    //Création du Vector perpendiculaire pour le dessin du ressort
    Vector perp = (G_CONST ^ r.getA()) ^ axe;
    perp = perp.unit();


    //Condition si le Vector A est colinéaire au Vector G
    if (r.getA() * Vector({1, 0, 0}) == 0 and r.getA() * Vector({0, 1, 0}) == 0){
        perp = Vector({1, 0, 0});
    }
    drawSpring3D(r.getO(), axe, perp);
    //dessineRessort2D(r.getO(), axe, perp);

    //Dessin de la sphère
    GLSphere sphere1;
    sphere1.initialize();

    QMatrix4x4 Pos_1;
    Pos_1.translate(v[1], v[2], v[3]);
    Pos_1.scale(0.1);
    drawSphere(Pos_1, sphere1, 1, 0, 0);
}

// ======================================================================

void ViewOpenGL::draw(SpringPendulum const& pr)
{
    Vector A = Vector({pr.getA()[1], pr.getA()[2], 0}).unit();
    //Vector position
    //Ici le Vector P est représenté par la position
    //(x, y) par rapport au point O avec les axes a
    // et g (y positif suivant g)
    Vector axe = pr.getP()[1] * A + pr.getP()[2] * (1.0/g_CONST) * G_CONST;
    Vector v = pr.getO() + axe;

    //Création du Vector perpendiculaire pour le dessin du ressort
    Vector perp = (G_CONST ^ pr.getA()) ^ axe;
    perp = perp.unit();

    if (pr.getA() * Vector({1, 0, 0}) == 0 and pr.getA() * Vector({0, 1, 0}) == 0){
        perp = Vector({1, 0, 0});
    }
    drawSpring3D(pr.getO(), axe, perp);
    //dessineRessort2D(pr.getO(), axe, perp);

    //Dessin de la sphère
    GLSphere sphere1;
    sphere1.initialize();

    QMatrix4x4 Pos_1;
    Pos_1.translate(v[1], v[2], v[3]);
    Pos_1.scale(0.1);
    drawSphere(Pos_1, sphere1, 1, 0, 0);
}

// ======================================================================

void ViewOpenGL::drawPhase(Oscillator const& o)
{

    prog.setUniformValue("vue_modele", matrix_view);
    glLineWidth(0.5);
    glBegin(GL_LINE_STRIP);

    //Couleur de la courbe dans l'espace des phases
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0);

    //On parcourt la liste de points et on les affiche
    for(auto & el : o.getCurve()){
        prog.setAttributeValue(SommetId, 0.0, el.x, el.y);
    }
    glEnd();
}
