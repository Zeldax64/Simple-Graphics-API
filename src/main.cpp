/*
	Special TODO: fix triangle intersect from MCube and MTriangle
	What next? List of TODOs!
	1) Finish implementation of worldBasisToCoord TMatrix.cpp; OK
	2) Create a Buffer/Color/Window class; Color Ok
	3) Do render; - Ok
			- Ray generation; Ok
			- Hit object system; Ok
			- Return a result (any color); Ok
	4) Implement materials - Ok
			- Create a material class; Ok
			- Return it when objected hitted; Ok
	5) Implement light sources - Ok
	6) Handle multiple objects render - Ok
	7) Handle ilumination render
			- Ambient Illumination - Ok
			- Diffuse Illumination - Ok
			- Specular Illumination - TODO

	TODO: Bug discover when rendering one sphere inside another!
	Try to use scn->hitRay(x_center, y_center) to debug!
*/

#include <iostream>

#include <math.h>

#include "core/math/Vertex3f.h"
#include "core/math/TMatrix.h"
#include "core/objects/meshes/MCube.h"
#include "core/objects/meshes/MTriangle.h"
#include "core/objects/geometric/GSphere.h"
#include "core/scenery/Scenery.h"
#include "core/renderer/RayCasting.h"
#include "core/light/Light.h"
#include "util/util.h"

#define X_WIDTH 500
#define Y_WIDTH 500

using namespace std;

void buildScenery(Scenery * scn) {
	/*
	TMatrix scale;
	scale.scale(1.0, 1.0, 1.0);
	TMatrix rotate;
	rotate.rotateY(-5.0);
	TMatrix translate;
	translate.translate(0.0, 0.0, 0.0);
	*/
	/*
	MCube* cube = new MCube();
	cube->applyTransform(scale);
	scn->addObj(cube);
	*/
	/*
	MTriangle* triangle = new MTriangle();
	triangle->applyTransform(translate*scale);
	scn->addObj(triangle);
	triangle->print();
	*/
	GSphere* sphere1 = new GSphere(Vertex3f(0.0, 0.0, 0.0),
																3.0,
																0.7, 0.5, 0.0);
	GSphere* sphere2 = new GSphere(Vertex3f(0.0, 0.0, 0.0),
																1.0,
																1.0, 1.0, 1.0
															);

	scn->addObj(sphere1);
	scn->addObj(sphere2);

	Light* light_src = new Light();
	light_src->setPosition(10.0, 10.0, 10.0);
	light_src->setAmbIntensity(1.0, 1.0, 1.0);
	light_src->setSourceIntensity(1.0, 1.0, 1.0);
	scn->addLight(light_src);
}

void buildCam(Vertex3f & pos, Vertex3f & look_at, Vertex3f & avup, float fov, Scenery * scn) {
	scn->setCamPos(pos);
	scn->setCamLookAt(look_at);
	scn->setCamAViewUp(avup);
	Camera* cam = scn->getCam();
	cam->setFOV(90.0);
	scn->calcCamCoord();
}

void renderScene(RayCasting & render) {
	Scenery* scn = render.getScenery();
	//scn->getObj(0)->print();
	scn->worldToCamTransform();
	render.render();

}

int main(int argc, char **argv) {
	// Build scenery
	Scenery scn;
	buildScenery(&scn);
	// Build camera
	Vertex3f cam_pos(10.0, 0.0, 0.0);
	Vertex3f look_at(0.0, 0.0, 0.0);
	Vertex3f avup(0.0, 1.0, 0.0);
	float fov = 90.0;
	buildCam(cam_pos, look_at, avup, fov, &scn);

	// Render
	RayCasting render(X_WIDTH, Y_WIDTH);
	render.setScenery(&scn);
	renderScene(render); // Render scene

	Color* buff = render.getBuffer(); // Get buffer

	mainGL(argc, argv, X_WIDTH, Y_WIDTH, buff);
}
