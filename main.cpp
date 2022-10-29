#include "raylib.h"
#include "iostream"
#include "player.cpp"

Texture2D textureGrid = { 0 };
// Camera cameraPlayer = { 0 };

// Scene drawing
void DrawScene(void)
{
    int count = 5;
    float spacing = 4;

    // Grid of cube trees on a plane to make a "world"
    DrawPlane((Vector3){ 0, 0, 0 }, (Vector2){ 50, 50 }, BEIGE); // Simple world plane

    for (float x = -count*spacing; x <= count*spacing; x += spacing)
    {
        for (float z = -count*spacing; z <= count*spacing; z += spacing)
        {
            DrawCubeTexture(textureGrid, (Vector3) { x, 1.5f, z }, 1, 1, 1, GREEN);
            DrawCubeTexture(textureGrid, (Vector3) { x, 0.5f, z }, 0.25f, 1, 0.25f, BROWN);
        }
    }

    DrawCubeTexture(textureGrid, (Vector3) { 3, 0.0f, 3 }, 1, 1, 1, RED);
}


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 900;
    const int screenHeight = 550;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - split screen");

    // Generate a simple texture to use for trees
    Image img = GenImageChecked(256, 256, 32, 32, DARKGRAY, WHITE);
    textureGrid = LoadTextureFromImage(img);
    UnloadImage(img);
    SetTextureFilter(textureGrid, TEXTURE_FILTER_ANISOTROPIC_16X);
    SetTextureWrap(textureGrid, TEXTURE_WRAP_CLAMP);

    Player player = Player();
    // // Setup player camera and screen
    // cameraPlayer.fovy = 45.0f;
    // cameraPlayer.up.y = 1.0f;
    // cameraPlayer.target.y = 1.0f;
    // cameraPlayer.position.z = -3.0f;
    // cameraPlayer.position.y = 1.0f;
    // cameraPlayer.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    SetCameraMode(player.GetCamera(), CAMERA_FIRST_PERSON);

    RenderTexture screenPlayer = LoadRenderTexture(screenWidth, screenHeight);

    // Build a flipped rectangle the size of the split view to use for drawing later
    Rectangle splitScreenRect = { 0.0f, 0.0f, (float) screenPlayer.texture.width, (float) -screenPlayer.texture.height };

    SetTargetFPS(144);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        // UpdateCamera(&cameraPlayer);
        player.MoveCamera();

        //----------------------------------------------------------------------------------
        float offsetThisFrame = 10.0f * GetFrameTime();

        // if (IsKeyDown(KEY_SPACE))
        // {
        //     cameraPlayer.position.y += 2.0f * offsetThisFrame;
            // cameraPlayer.up.y = 2.0f;
            // cameraPlayer.target.y = 2.0f;
        // }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        // Draw Player view to the render texture

        BeginTextureMode(screenPlayer);
            ClearBackground(SKYBLUE);
            BeginMode3D(player.GetCamera());
                DrawScene();
            EndMode3D();
        EndTextureMode();


        // Draw both views render textures to the screen side by side
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTextureRec(screenPlayer.texture, splitScreenRect, (Vector2){ 0, 0 }, WHITE);
        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadRenderTexture(screenPlayer); // Unload render texture
    UnloadTexture(textureGrid);         // Unload texture

    CloseWindow();                      // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}