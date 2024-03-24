#include "Renderer.h"

void Renderer::init(int width, int height)
{
	m_Camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -90.0f, 2.5f, 0.1f);


	float planeVerticies[] = {
		// position				//TEXTURE COORDS
		-20.0f, 0.0f, -20.0f,	0.0f, 0.0f,
		20.0f, 0.0f, -20.0f,	10.0f, 0.0f,
		-20.0f, 0.0f, 20.0f,	0.0f, 10.0f,

		-20.0f, 0.0f, 20.0f,	0.0f, 10.0f,
		20.0f, 0.0f, 20.0f,		10.0f, 10.0f,
		20.0f, 0.0f, -20.0f,	10.0f, 0.0f,
	};

	float cubeVerticies[] = {
		 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		  0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		 -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		  0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		 -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		 -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		 -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		 -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		 -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		 -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		  0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		  0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		 -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		  0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		 -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		  0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};


	shader = Shader("resources/shaders/shader.vs", "resources/shaders/shader.fs");
	lightSourceShader = Shader("resources/shaders/lightSourceShader.vs", "resources/shaders/lightSourceShader.fs");
	planeShader = Shader("resources/shaders/planeShader.vs", "resources/shaders/planeShader.fs");

	//stbi_set_flip_vertically_on_load(true);

	//Model ourModel("resources/models/trees.obj");

	m_Width = width;
	m_Height = height;

	//-------------------- Normal VAO Setup ----------------------
	//Create vertex array object
	glGenVertexArrays(1, &glContext.VAO);
	glBindVertexArray(glContext.VAO);

	// Create vertex buffer object for verticie data
	glGenBuffers(1, &glContext.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, glContext.VBO);

	// bind data to vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerticies), cubeVerticies, GL_STATIC_DRAW);

	// -------------------- LINK VERTEX ATTRIB POINTERS
	// params (index, size, type, normalized, stride, pointer)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//-------------------- Normal VAO Setup ----------------------
	//Create vertex array object
	glGenVertexArrays(1, &glContext.lightSourceVAO);
	glBindVertexArray(glContext.lightSourceVAO);

	// Create vertex buffer object for verticie data
	glGenBuffers(1, &glContext.lightSourceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, glContext.lightSourceVBO);

	// bind data to vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerticies), cubeVerticies, GL_STATIC_DRAW);

	// -------------------- LINK VERTEX ATTRIB POINTERS
	// params (index, size, type, normalized, stride, pointer)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



	//-------------------- plane VAO Setup ----------------------
	//Create vertex array object
	glGenVertexArrays(1, &glContext.planeVAO);
	glBindVertexArray(glContext.planeVAO);

	// Create vertex buffer object for verticie data
	glGenBuffers(1, &glContext.planeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, glContext.planeVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVerticies), planeVerticies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glEnable(GL_DEPTH_TEST);


	glContext.dirtTextureID = GetTextureFromFile("resources/textures/dirt.png", "test", false);

}

void Renderer::onUpdate()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::mat4 view;
	view = m_Camera.getViewMatrix();
	glm::vec3 camPos = m_Camera.getCameraPos();
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), ((float)800) / ((float)600), 0.1f, 100.0f);

	
	//-------------------- Render Light Source ----------------------
	lightSourceShader.useProgram();
	glm::vec3 lightPos(1.0f, 1.0f, 2.0f);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f));

	lightSourceShader.setMat4("model", model);

	//shader.setMat4("model", transform);
	lightSourceShader.setMat4("view", view);
	lightSourceShader.setMat4("projection", proj);

	glBindVertexArray(glContext.lightSourceVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//-------------------- Render Other VAO ----------------------

	shader.useProgram();

	//apply rotation to triangle
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::rotate(transform, glm::radians(60.0f * ((float)glfwGetTime())), glm::vec3(0.0f, 1.0f, 0.0f));

	// render the loaded model
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(60.0f * ((float)glfwGetTime())), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);

	//shader.setMat4("model", transform);
	shader.setMat4("view", view);
	shader.setMat4("projection", proj);
	glm::vec3 cubeColor(0.5f, 0.2f, 1.0f);
	shader.setVec3("objectColor", cubeColor);
	shader.setVec3("lightColor",lightColor);
	shader.setVec3("lightPos", lightPos);
	shader.setVec3("viewPos", camPos);
	shader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
	shader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
	shader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	shader.setFloat("material.shininess", 32.0f);
	glBindVertexArray(glContext.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	planeShader.useProgram();
	glBindVertexArray(glContext.planeVAO);
	glBindTexture(GL_TEXTURE_2D, glContext.dirtTextureID);

	planeShader.setMat4("view", view);
	planeShader.setMat4("projection", proj);
	planeShader.setVec3("lightColor", lightColor);
	planeShader.setVec3("lightPos", lightPos);
	planeShader.setVec3("viewPos", camPos);
	planeShader.setVec3("material.ambient", 0.05f, 0.05f, 0.05f);
	planeShader.setVec3("material.diffuse", 0.5f, 0.5f, 0.5f);
	planeShader.setVec3("material.specular", 0.2f, 0.2f, 0.2f);
	planeShader.setFloat("material.shininess",64.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -0.52f, 0.0f));
	shader.setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::updateViewport(int width, int height)
{
	glViewport(0, 0, width, height);
}

Camera* Renderer::getCamera()
{
	return &m_Camera;
}

void Renderer::cleanup()
{
	glDeleteVertexArrays(1, &glContext.VAO);
	glDeleteBuffers(1, &glContext.VBO);

}


