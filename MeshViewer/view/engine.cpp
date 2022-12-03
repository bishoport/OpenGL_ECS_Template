#include "engine.h"


Engine::Engine(int width, int height) {

	shader = util::load_shader("shaders/vertex.txt", "shaders/fragment.txt");
	glUseProgram(shader);

	glUniform1i(glGetUniformLocation(shader, "basicTexture"), 0);

	float aspectRatio = (float)width / float(height);
	//set up framebuffer
	glClearColor(0.5f, 0.1f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glm::mat4 projection_transform = glm::perspective(45.0f, aspectRatio, 0.1f, 10.0f);
	glUniformMatrix4fv(
		glGetUniformLocation(shader, "projection"), 
		1, GL_FALSE, glm::value_ptr(projection_transform)
	);

}

Engine::~Engine() 
{

	glDeleteProgram(shader);
}



void Engine::render(Scene* scene) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//prepare shaders
	glm::mat4 view_transform{
		glm::lookAt(
			scene->mainCamera->getComponent<Transform>().position, //eye -> camera position
			glm::vec3{0.0f,0.0f,0.0f}, //center -> taget position
			glm::vec3{0.0f,0.0f,1.0f} // up -> The up vector is basically a vector defining your world's "upwards" direction
		)
	};

	//glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE,
	//	glm::value_ptr(view_transform));

	//glm::mat4 model_transform{ glm::mat4(1.0f) };
	//model_transform = glm::translate(model_transform, scene->player->getComponent<Transform>().position);
	//model_transform =
	//	model_transform * glm::eulerAngleXYZ(
	//		scene->player->getComponent<Transform>().eulers.x, 
	//		scene->player->getComponent<Transform>().eulers.y, 
	//		scene->player->getComponent<Transform>().eulers.z
	//	);
	//glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model_transform));

	//glUseProgram(shader);
	//scene->player->getComponent<MaterialComp>().use();
	//glBindVertexArray(scene->player->getComponent<MeshFilter>().VAO);
	//glDrawArrays(GL_TRIANGLES, 0, scene->player->getComponent<MeshFilter>().vertexCount);


	
	for (int i = 0; i < scene->entitiesInScene.size(); i++)
	{
		glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE,
			glm::value_ptr(view_transform));

		glm::mat4 model_transform{ glm::mat4(1.0f) };
		model_transform = glm::translate(model_transform, scene->entitiesInScene[i]->getComponent<Transform>().position);
		model_transform =
			model_transform * glm::eulerAngleXYZ(
				scene->entitiesInScene[i]->getComponent<Transform>().eulers.x, 
				scene->entitiesInScene[i]->getComponent<Transform>().eulers.y, 
				scene->entitiesInScene[i]->getComponent<Transform>().eulers.z
			);
		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model_transform));

		glUseProgram(shader);
		scene->entitiesInScene[i]->getComponent<MaterialComp>().use();
		glBindVertexArray(scene->entitiesInScene[i]->getComponent<MeshFilter>().VAO);
		glDrawArrays(GL_TRIANGLES, 0, scene->entitiesInScene[i]->getComponent<MeshFilter>().vertexCount);
	}
}