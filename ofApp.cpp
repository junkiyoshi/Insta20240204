#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->noise_param = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->noise_param += 0.00005;
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	float v_span = 1;
	float u_span = 90;
	int R = 230;
	int r = 70;
	
	ofColor color;
	float noise_seed = ofRandom(1000);
	float noise_span = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.008), 0, 1, 0, 4);
	for (float v = 0; v < 360; v += v_span) {

		int u_start = ofMap(ofNoise(noise_seed, cos(v * DEG_TO_RAD) * noise_span, sin(v * DEG_TO_RAD) * noise_span, this->noise_param), 0, 1, -360, 360);
		int next_u = ofMap(ofNoise(noise_seed, cos((v + v_span) * DEG_TO_RAD) * noise_span, sin((v + v_span) * DEG_TO_RAD) * noise_span, this->noise_param), 0, 1, -360, 360);
		for (float u = u_start; u < u_start + 360; u += u_span) {

			color.setHsb(ofMap(u, u_start, u_start + 360, 0, 255), 200, 255);
			ofSetColor(color);

			ofDrawLine(this->make_point(R, r, u, v), this->make_point(R, r, next_u, v + v_span));
			next_u += u_span;
		}
	}

	this->cam.end();

	/*
	int start = 220;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	//auto z = r * sin(u);

	return glm::vec3(x, y, 0);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
