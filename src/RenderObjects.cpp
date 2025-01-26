#include "RenderObjects.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "utils/logger.h"

// Add a new renderable object
void RenderObjects::addObject(
    std::vector<float> vertexData,
    std::unique_ptr<Shader> shader,
    std::vector<Texture> tex,
    const glm::vec3& pos,
    const glm::vec3& rot,
    const glm::vec3& scl
) {
    uint64_t vaoCnt = vaos.size();
    vaos.push_back(0);
    vbos.push_back(0);
    ebos.push_back(0);

    glGenVertexArrays(1, &vaos[vaoCnt]);
    glGenBuffers(1, &vbos[vaoCnt]);

    glBindVertexArray(vaos[vaoCnt]);

    glBindBuffer(GL_ARRAY_BUFFER, vbos[vaoCnt]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos[vaoCnt]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexData), &vertexData, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Store vertex data
    vertices.emplace_back(std::move(vertexData));

    // Move shader into the shaders vector
    shaders.emplace_back(std::move(shader));

    // Move textures into the textures vector
    textures.emplace_back(std::move(tex));

    // Store transformation data
    positions.push_back(pos);
    rotations.push_back(rot);
    scales.push_back(scl);
}

// Render all objects
void RenderObjects::render() {
    for (size_t i = 0; i < shaders.size(); ++i) {
        Shader* currentShader = shaders[i].get();
        if (!currentShader) {
            std::cerr << "Shader at index " << i << " is null.\n";
            continue;
        }

        // 1. bind textures on corresponding texture units
        // 2. activate shader
        // 3. create transformations
        // 4. render container

        // Use the shader program
        currentShader->Use();

        // Bind textures
        for (size_t t = 0; t < textures[i].size(); ++t) {
            textures[i][t].Use(static_cast<unsigned int>(t));
            // Assuming shader uniform names are "ourTexture0", "ourTexture1", etc.
            currentShader->setInt("ourTexture" + std::to_string(t), static_cast<int>(t));
        }

        
        glm::mat4 model         = glm::mat4(1.0f);
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        currentShader->setMat4("view", view);
        currentShader->setMat4("model", model);
        currentShader->setMat4("projection", projection);

        // Set the model matrix uniform
        // currentShader->setMat4("model", model);

        // Bind VAO and draw
        glBindVertexArray(vaos[i]);

        // 5 floats per vertex
        size_t vertexCount = vertices[i].size() / 5;
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // glBindVertexArray(0);
        // LOG(INFO, (std::string("Rendered object ") + std::to_string(i)).c_str());
    }


    // 1. bind textures on corresponding texture units
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, texture1);
    // glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D, texture2);

    // 2. activate shader
    // ourShader.use();
    
    // 3. create transformations
    // glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    // glm::mat4 view          = glm::mat4(1.0f);
    // glm::mat4 projection    = glm::mat4(1.0f);
    // model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    // projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    // // retrieve the matrix uniform locations
    // unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
    // unsigned int viewLoc  = glGetUniformLocation(ourShader.ID, "view");
    // // pass them to the shaders (3 different ways)
    // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    // // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    // ourShader.setMat4("projection", projection);

    // 4. render container
    // glBindVertexArray(VAO);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // // -------------------------------------------------------------------------------
    // glfwSwapBuffers(window);
    // Reset active texture to default
    // glActiveTexture(GL_TEXTURE0);
}
