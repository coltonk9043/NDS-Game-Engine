/*
// Colton Kennedy - Engine 2
// 10/20/2022
*/

#include <nds.h>
#include <stdlib.h>
#include <stdio.h>

//texture_bin.h is created automagicaly from the texture.bin placed in arm9/resources
//texture.bin is a raw 128x128 16 bit image.  I will release a tool for texture conversion 
//later
#include "texture_bin.h"

// Defined header files. 
#include "GameObject.h"
#include "SceneGraph.h"
#include "Common.h"

// A global polygon count
namespace Counter{
	int Counter::Polygons::count = 0;
}

//Verticies for the cube
v16 CubeVectors[] = {
 		floattov16(-0.5), floattov16(-0.5), floattov16(0.5), 
		floattov16(0.5),  floattov16(-0.5), floattov16(0.5),
		floattov16(0.5),  floattov16(-0.5), floattov16(-0.5),
		floattov16(-0.5), floattov16(-0.5), floattov16(-0.5),
		floattov16(-0.5), floattov16(0.5),  floattov16(0.5), 
		floattov16(0.5),  floattov16(0.5),	floattov16(0.5),
		floattov16(0.5),  floattov16(0.5),  floattov16(-0.5),
		floattov16(-0.5), floattov16(0.5),  floattov16(-0.5)
};

// Polygons of the cube.
u8 CubeFaces[] = {
	3,2,1,0,
	0,1,5,4,
	1,2,6,5,
	2,3,7,6,
	3,0,4,7,
	5,6,7,4
};

// Texture coordinates for the cube.
u32 uv[] = {
	TEXTURE_PACK(inttot16(128), 0), TEXTURE_PACK(inttot16(128),inttot16(128)), TEXTURE_PACK(0, inttot16(128)), TEXTURE_PACK(0,0)
};

u32 normals[] = {
	NORMAL_PACK(0,floattov10(-.97),0), NORMAL_PACK(0,0,floattov10(.97)), NORMAL_PACK(floattov10(.97),0,0),
	NORMAL_PACK(0,0,floattov10(-.97)), NORMAL_PACK(floattov10(-.97),0,0), NORMAL_PACK(0,floattov10(.97),0)
};

int main()
{	
	// Declares integers for the default texture, polygon count, and vertex count;
	int textureID, polygon_count, vertex_count;

	//set mode 0, enable BG0 and set it to 3D
	videoSetMode(MODE_0_3D);
	videoSetModeSub(MODE_0_2D);

	// Initializes the default console.
	consoleDemoInit();

	// Initialize GL and enable Texutres
	glInit();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ANTIALIAS);

	// setup the rear plane
	glClearColor(0,0,0,31); // BG must be opaque for AA to work
	glClearPolyID(63); // BG must have a unique polygon ID for AA to work
	glClearDepth(0x7FFF);

	glViewport(0,0,255,191);

	// Generates NDS GL Material properties.
	glMaterialf(GL_AMBIENT, RGB15(8,8,8));
	glMaterialf(GL_DIFFUSE, RGB15(16,16,16));
	glMaterialf(GL_SPECULAR, BIT(15) | RGB15(8,8,8));
	glMaterialf(GL_EMISSION, RGB15(5,5,5));
	glMaterialShinyness();

	// Sets our VRAM banks.
	vramSetBankA(VRAM_A_TEXTURE);
	vramSetBankB(VRAM_B_LCD);

	// Texture Loading
    glGenTextures(1, &textureID);
    glBindTexture(0, textureID);
	glTexImage2D(0, 0, GL_RGB, TEXTURE_SIZE_128 , TEXTURE_SIZE_128, 0, TEXGEN_TEXCOORD, (u8*)texture_bin);

	REG_DISPCAPCNT = 
			DCAP_MODE(DCAP_MODE_BLEND) //blend source A and source B
		|	DCAP_SRC_B(DCAP_SRC_B_VRAM)
		|	DCAP_SRC_A(DCAP_SRC_A_3DONLY)
		|	DCAP_SIZE(DCAP_SIZE_256x192)
		|	DCAP_OFFSET(0) //where to write the captured data within our chosen VRAM bank
		|	DCAP_BANK(DCAP_BANK_VRAM_B)
		|	DCAP_B(12) //blend mostly from B to make a very dramatic effect
		|	DCAP_A(4); //and blend only a little bit from the new scene
		
	// Defines our basic Scene Graph using GameObjects
	GameObject* root = new GameObject({0,0,0}, {0,0,0}, {1,1,1});
	Camera* camera = new Camera({0,0,-1.0f}, {0.0f, 0.0f, 0.0f}, {1,1,1});
	MeshedObject* meshedObject = new MeshedObject({0,0,0}, {0,0,0}, {1,1,1}, {CubeVectors, CubeFaces, uv, normals, (sizeof(CubeFaces)/sizeof(u8))/4}, textureID);
	ColouredObject* meshedObject2 = new ColouredObject({2,0,1.5}, {30,0,0}, {1,2,1}, {CubeVectors, CubeFaces, uv, normals, (sizeof(CubeFaces)/sizeof(u8))/4}, {0.0f,1.0f,0.0f});
	MeshedObject* meshedObject3 = new MeshedObject({0,1,-2}, {45,0,0}, {1,1,1}, {CubeVectors, CubeFaces, uv, normals, (sizeof(CubeFaces)/sizeof(u8))/4}, textureID);

	// Create our scenegraph
	SceneGraph sceneGraph {root};
	sceneGraph.addObject(root, camera);
	sceneGraph.addObject(root, meshedObject);
	sceneGraph.addObject(root, meshedObject2);
	sceneGraph.addObject(meshedObject2, meshedObject3);

	// Game loop.
	while(1) {
		// Reset the polygon count to 0.
		Counter::Polygons::count = 0;

		// Game Update Logic
		// Scans for keys.
		scanKeys();
		u16 keys = keysHeld();
		// If X is down, randomly create new cubes and add them to the scenegraph.
		if (keys & KEY_X){
			int r = rand() % 2;
			GameObject* gm;
			if(r == 0){
				gm = new MeshedObject({rand() % 10 - 5.0f,rand() % 10 - 5.0f,rand() % 10 - 5.0f}, {rand() % 180,rand() % 180,0}, {1,1,1}, {CubeVectors, CubeFaces, uv, normals, (sizeof(CubeFaces)/sizeof(u8))/4}, textureID);
			}else{
				gm = new ColouredObject({rand() % 10 - 5.0f,rand() % 10 - 5.0f,rand() % 10 - 5.0f}, {rand() % 180,rand() % 180,0}, {1,2,1}, {CubeVectors, CubeFaces, uv, normals, (sizeof(CubeFaces)/sizeof(u8))/4}, {rand() / double(RAND_MAX),rand() / double(RAND_MAX),rand() / double(RAND_MAX)});
			}
			sceneGraph.addObject(root, gm);
		}

		// Rotates one of the meshed objects to show rotation.
		sceneGraph.rotateObject(meshedObject2, 0, 2, 0);

		// Updates the scene graph.
		sceneGraph.Update(keys);

		// OpenGL Lights
		glLight(0, RGB15(31,31,31) , 0,				   		floattov10(-1.0),	0);
		glLight(1, RGB15(31,0,31),   0,				   		floattov10(1) - 1,	0);
		glLight(2, RGB15(0,31,0) ,   floattov10(-1.0), 		0,					0);
		glLight(3, RGB15(0,0,31) ,   floattov10(1.0) - 1,  	0,					0);

		// Pushes the GL Projection Matrix to the matrix stack.
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(70, 256.0 / 192.0, 0.1, 10);

		glPolyFmt(POLY_ALPHA(31) | POLY_CULL_BACK | POLY_FORMAT_LIGHT0 | POLY_FORMAT_LIGHT1 | POLY_FORMAT_LIGHT2 | POLY_FORMAT_LIGHT3);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Applies the transformation matrix generated by the camera's transform.
		camera->applyViewingTransformation();
		
		// Draws the Scene Graph
		sceneGraph.Draw();

		// Waits for a screen refresh and waits till the render engine is not busy.
		swiWaitForVBlank();
		while (GFX_STATUS & (1<<27));

		// Prints out debug data and controls.
		consoleClear();
		printf("          Controls:\n\n");
		printf("D-PAD   - Rotate Camera\n");
		printf("A/B     - Move Camera\n");
		printf("X       - Increase cube count.\n\n");
		Vector3 position = camera->GetTransform()->position;
		Vector3 rotation = camera->GetTransform()->rotation;
		printf("The camera is positioned at: \n\tX: %f\n\tY: %f\n\tZ: %f\n", position.x, position.y, position.z);
		printf("The camera is rotated by: \n\tYaw: %f\n\tPitch: %f\n\tRoll: %f\n\n", rotation.x, rotation.y, rotation.z);

		// Gets Vertex and Polygon RAM count and displays it.
		glGetInt(GL_GET_VERTEX_RAM_COUNT, &vertex_count);
		glGetInt(GL_GET_POLYGON_RAM_COUNT, &polygon_count);
		printf("\nObject Count: %i\n", sceneGraph.getNumberOfObjects());
		printf("\nVertex Count: %i/16000\n", vertex_count);
		printf("Polygon Count: %i/4000\n", polygon_count);

		glFlush(0);
	}

	return 0;
}
