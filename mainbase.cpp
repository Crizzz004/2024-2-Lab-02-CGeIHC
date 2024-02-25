#include <stdio.h>
#include <glew.h>
#include <glfw3.h>

//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600;

int main()
{
    //Inicializaci�n de GLFW
    if (!glfwInit())
    {
        printf("Fall� inicializar GLFW");
        glfwTerminate();
        return 1;
    }
    //Asignando variables de GLFW y propiedades de ventana
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //para solo usar el core profile de OpenGL y no tener retrocompatibilidad
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //CREAR VENTANA
    GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Primer ventana", NULL, NULL);

    if (!mainWindow)
    {
        printf("Fallo en crearse la ventana con GLFW");
        glfwTerminate();
        return 1;
    }
    //Obtener tama�o de Buffer
    int BufferWidth, BufferHeight;
    glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

    //asignar el contexto
    glfwMakeContextCurrent(mainWindow);

    //permitir nuevas extensiones
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        printf("Fall� inicializaci�n de GLEW");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    // Asignar valores de la ventana y coordenadas
    //Asignar Viewport
    glViewport(0, 0, BufferWidth, BufferHeight);
    printf("Version de Opengl: %s \n", glGetString(GL_VERSION));
    printf("Marca: %s \n", glGetString(GL_VENDOR));
    printf("Renderer: %s \n", glGetString(GL_RENDERER));
    printf("Shaders: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    // Colores en una secuencia (rojo, verde, azul, repetir)
    float red[] = { 1.0f, 0.0f, 0.0f };   // Rojo
    float green[] = { 0.0f, 1.0f, 0.0f }; // Verde
    float blue[] = { 0.0f, 0.0f, 1.0f };  // Azul

    float* colors[] = { red, green, blue };
    int numColors = sizeof(colors) / sizeof(colors[0]);
    int currentColorIndex = 0;

    // Variables para manejar el tiempo
    double lastTime = glfwGetTime();
    double elapsedTime = 0.0;
    double colorChangeInterval = 1.0; // Cambio de color cada 1 segundo

    //Loop mientras no se cierra la ventana
    while (!glfwWindowShouldClose(mainWindow))
    {
        // Medir el tiempo transcurrido
        double currentTime = glfwGetTime();
        elapsedTime += currentTime - lastTime;
        lastTime = currentTime;

        // Recibir eventos del usuario
        glfwPollEvents();

        // Cambiar el color de fondo de la ventana cada 'colorChangeInterval' segundos
        if (elapsedTime >= colorChangeInterval)
        {
            // Cambiar al siguiente color
            currentColorIndex = (currentColorIndex + 1) % numColors;

            // Establecer el nuevo color de fondo
            glClearColor(colors[currentColorIndex][0], colors[currentColorIndex][1], colors[currentColorIndex][2], 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(mainWindow);

            // Reiniciar el tiempo transcurrido
            elapsedTime = 0.0;
        }
    }

    return 0;
}
