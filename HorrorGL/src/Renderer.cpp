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

	m_Width = width;
	m_Height = height;

	//Create vertex array object
	glGenVertexArrays(1, &glContext.VAO);
	glBindVertexArray(glContext.VAO);

	// Create vertex buffer object for verticie data
	glGenBuffers(1, &glContext.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, glContext.VBO);

	// bind data to vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	shader = Shader("resources/shaders/shader.vs", "resources/shaders/shader.fs");

	//stbi_set_flip_vertically_on_load(true);

	//Model ourModel("resources/models/trees.obj");

	// -------------------- LINK VERTEX ATTRIB POINTERS
	// params (index, size, type, normalized, stride, pointer)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	glEnable(GL_DEPTH_TEST);

	glContext.dirtTextureID = GetTextureFromFile("resources/textures/dirt.png", "test", false);
}

void Renderer::onUpdate()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.useProgram();

	//apply rotation to triangle
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::rotate(transform, glm::radians(60.0f * ((float)glfwGetTime())), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 view;
	view = m_Camera.getViewMatrix();

	/*NOTE: ran into a bug where i didn't use a view matrix and couldn't see triangle
	 this was because the "camera" and triangle were both centered at 0.
	 had to eithers translate the triangle in the -z direction
	or create a view matrix*/
	// create view (camera)
	//glm::mat4 view = glm::mat4(1.0f);
	//translate the scene in the reverse direction of where we want to move
	//view = glm::translate(view, glm::vec3(x, 0.0f, z));

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), ((float)800) / ((float)600), 0.1f, 100.0f);

	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(60.0f * ((float)glfwGetTime())), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);

	//shader.setMat4("model", transform);
	shader.setMat4("view", view);
	shader.setMat4("projection", proj);

	glBindTexture(GL_TEXTURE_2D, texture);
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


