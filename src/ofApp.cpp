#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    //float myArray[7];
    //myArray[0] = image1.load("sea1.jpg");
    //myArray[1] = image2.load("sea2.jpg");
    //myArray[2] = image3.load("sea3.jpg");
    //myArray[3] = image4.load("sea4.jpg");
    //myArray[4] = image5.load("sea5.jpg");
    //myArray[5] = image6.load("sea6.jpg");
    //myArray[6] = image7.load("sea7.jpg");


    image1.load("sea1.jpg");
    //image2.load("sea2.jpg");
    //image3.load("sea3.jpg");
    //image4.load("sea4.jpg");
    //image5.load("sea5.jpg");
    //image6.load("sea6.jpg");
    //image7.load("sea7.jpg");


    image1.resize(200, 200);

    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.enableIndices();

    ofSetFrameRate(60);

    float intensityThreshold = 150.0;
    int w = image1.getWidth();
    int h = image1.getHeight();
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            ofColor c = image1.getColor(x, y);
            float intensity = c.getLightness();
            if (intensity >= intensityThreshold) {
                float saturation = c.getSaturation();
                float z = ofMap(saturation, 0, 255, -100, 100);
                ofVec3f pos(x * 4, y * 4, z);
                mesh.addVertex(pos);
                mesh.addColor(c);

            }
        }
        offsets.push_back(ofVec3f(ofRandom(0, 100000), ofRandom(0, 100000), ofRandom(0, 100000)));
    }
    float connectionDistance = 30;
    int numVerts = mesh.getNumVertices();
    for (int a = 0; a < numVerts; ++a) {
        ofVec3f verta = mesh.getVertex(a);
        for (int b = a + 1; b < numVerts; ++b) {
            ofVec3f vertb = mesh.getVertex(b);
            float distance = verta.distance(vertb);
            if (distance <= connectionDistance) {
                // In OF_PRIMITIVE_LINES, every pair of vertices or indices will be
                // connected to form a line
                mesh.addIndex(a);
                mesh.addIndex(b);

                offsets.push_back(ofVec3f(ofRandom(0, 100000), ofRandom(0, 100000), ofRandom(0, 100000)));
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    int numVerts = mesh.getNumVertices();
    for (int i = 0; i < numVerts; ++i) {
        ofVec3f vert = mesh.getVertex(i);

        float time = ofGetElapsedTimef();
        float timeScale = 5.0;
        float displacementScale = 0.75;
        ofVec3f timeOffsets = offsets[i];

        vert.x += (ofSignedNoise(time * timeScale + timeOffsets.x)) * displacementScale;
        vert.y += (ofSignedNoise(time * timeScale + timeOffsets.y)) * displacementScale;
        vert.z += (ofSignedNoise(time * timeScale + timeOffsets.z)) * displacementScale;
        mesh.setVertex(i, vert);
    }
   
}

//--------------------------------------------------------------
void ofApp::draw() {

    ofColor centerColor = ofColor(85, 78, 68);
    ofColor edgeColor(0, 0, 0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);

    easyCam.begin();
    ofPushMatrix();
    ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2);
    mesh.draw();
    ofPopMatrix();
    easyCam.end();
    cout << mesh.getNumVertices() << endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
