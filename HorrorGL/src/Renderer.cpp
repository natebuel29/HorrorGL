#include "Renderer.h"

void Renderer::init(int width, int height)
{
	m_Camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -90.0f, 2.5f, 0.1f);

	float verticies[] = {
		// position			// colors			//texture coords
		-0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	-1.0f, 0.0f,
		0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	-1.0f, 0.0f,
		0.0f, 0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	-1.0f, 0.0f,
		// position			// colors
		-20.0f, 0.0f, -20.0f,	0.2f, 0.2f, 0.2f,	0.0f, 0.0f,
		20.0f, 0.0f, -20.0f,	0.2f, 0.2f, 0.2f,	10.0f, 0.0f,
		-20.0f, 0.0f, 20.0f,	0.2f, 0.2f, 0.2f,	0.0f, 10.0f,

		-20.0f, 0.0f, 20.0f,	0.2f, 0.2f, 0.2f,	0.0f, 10.0f,
		20.0f, 0.0f, 20.0f,		0.2f, 0.2f, 0.2f,	10.0f, 10.0f,
		20.0f, 0.0f, -20.0f,	0.2f, 0.2f, 0.2f,	10.0f, 0.0f,
	};

	float lightSourceVerticies[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	
	
	};


	shader = Shader("resources/shaders/shader.vs", "resources/shaders/shader.fs");
	lightSourceShader = Shader("resources/shaders/lightSourceShader.vs", "resources/shaders/lightSourceShader.fs");

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	// -------------------- LINK VERTEX ATTRIB POINTERS
	// params (index, size, type, normalized, stride, pointer)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	//-------------------- Light Source VAO Setup ----------------------
	//Create vertex array object
	glGenVertexArrays(1, &glContext.lightSourceVAO);
	glBindVertexArray(glContext.lightSourceVAO);

	// Create vertex buffer object for verticie data
	glGenBuffers(1, &glContext.lightSourceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, glContext.lightSourceVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(lightSourceVerticies), lightSourceVerticies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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

	/*NOTE: ran into a bug where i didn't use a view matrix and couldn't see triangle
	 this was because the "camera" and triangle were both centered at 0.
	 had to eithers translate the triangle in the -z direction
	or create a view matrix*/
	// create view (camera)
	//glm::mat4 view = glm::mat4(1.0f);
	//translate the scene in the reverse direction of where we want to move
	//view = glm::translate(view, glm::vec3(x, 0.0f, z));


	// render the loaded model
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(60.0f * ((float)glfwGetTime())), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);

	//shader.setMat4("model", transform);
	shader.setMat4("view", view);
	shader.setMat4("projection", proj);
	shader.setVec3("lightColor",lightColor);


	glBindTexture(GL_TEXTURE_2D, glContext.dirtTextureID);
	glBindVertexArray(glContext.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//apply rotation to triangle
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -0.52f, 0.0f));
	shader.setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 3, 9);
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


