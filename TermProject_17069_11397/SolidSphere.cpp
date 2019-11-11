#include "SolidSphere.h"
#include <math.h>

SolidSphere::SolidSphere(float r, int sl, int st) : SolidShape3D() {
	properties.setXYZ(r, sl, st);
}

SolidSphere::SolidSphere(const SolidSphere& sph) : SolidShape3D(sph) {
	properties = sph.properties;
}

Vector3 SolidSphere::getProperties() const{
	return properties;
}

bool SolidSphere::collisionDetection(const SolidSphere& sph) {
	if (dotProduct(getCenter() - sph.getCenter(), getCenter() - sph.getCenter())
		<= pow((getProperties()[0] + sph.getProperties()[0]),2)) {
		return true;
	}
	else
	return false;
}

void SolidSphere::collisionHandling(SolidSphere& sph) {
	if (collisionDetection(sph)) {
		setVelocity(getVelocity() - (dotProduct(getVelocity(), sph.getVelocity())
				/ dotProduct(getCenter() - sph.getCenter(), getCenter() - sph.getCenter()))
			* (getCenter() - sph.getCenter()));
		sph.setVelocity(sph.getVelocity() - (dotProduct(sph.getVelocity(), getVelocity())
			/ dotProduct(sph.getCenter() - getCenter(), sph.getCenter() - getCenter()))
			* (sph.getCenter() - getCenter()));
	}
}

void SolidSphere::draw() const {
	glPushMatrix();

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_EMISSION, mtl.getEmission());
	glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.getAmbient());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.getDiffuse());
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.getSpecular());
	glMaterialfv(GL_FRONT, GL_SHININESS, mtl.getShininess());

	glTranslatef(center[0], center[1], center[2]);
	glutSolidSphere(properties[0], properties[1], properties[2]);
	glPopMatrix();
}