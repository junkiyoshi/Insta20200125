#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();
	this->frame.clear();

	int len = 300;
	int width = 20;
	for (int z = -len; z <= len; z += width) {

		int start_param = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, 100, 200);
		int noise_value = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, 25, 100);
		int end_param = start_param + noise_value;
		int start_index = this->mesh.getNumVertices();
		for (int param = start_param; param <= end_param; param++) {

			int index = mesh.getNumVertices() - 2;

			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec3(this->make_point(len, param), z + width * 0.5));
			vertices.push_back(glm::vec3(this->make_point(len, param), z - width * 0.5));

			mesh.addVertices(vertices);
			frame.addVertices(vertices);

			if (index > start_index) {

				mesh.addIndex(index + 0); mesh.addIndex(index + 1); mesh.addIndex(index + 3);
				mesh.addIndex(index + 0); mesh.addIndex(index + 2); mesh.addIndex(index + 3);

				frame.addIndex(index + 0); frame.addIndex(index + 2);
				frame.addIndex(index + 1); frame.addIndex(index + 3);
			}

			if (param % 25 == 0) {

				frame.addIndex(frame.getNumVertices() - 1); frame.addIndex(frame.getNumVertices() - 2);
			}
		}

		frame.addIndex(start_index); frame.addIndex(start_index + 1);
		frame.addIndex(frame.getNumVertices() - 1); frame.addIndex(frame.getNumVertices() - 2);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(90);
	ofRotateZ(45);

	ofSetColor(39);
	this->mesh.draw();

	ofSetColor(239);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}