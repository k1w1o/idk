#include "raylib.h"
#include <iostream>



int main() {
    // ��������� �������� � ������
    int screenWidth = 800;
    int screenHeight = 600;
    int squareSize = 50;
    int speedX = 5;         // �������� �������� �� ��� X
    int jumpHeight = 200;    // ������������ ������ ������
    float gravity = 1.0f;    // ���� ����������
    float jumpSpeed = 15.0f; // ��������� �������� ������

    // ��������� ��������
    int squareX = screenWidth / 2 - squareSize / 2;
    int squareY = screenHeight - squareSize;
    bool isJumping = false;
    float velocityY = 0;

    int posX1 = 200, posY1 = 500;

    InitWindow(screenWidth, screenHeight, "Moving and Jumping Square");



    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // �������� �������� ��������������� ��� ������ � �����������
        Rectangle playerRec = { (float)squareX, (float)squareY, 50.0f, 50.0f };
        Rectangle obstacleRec = { (float)posX1, (float)posY1, 50.0f, 50.0f };

        // �������� ����� � ������
        if (IsKeyDown(KEY_A)) squareX -= speedX;
        if (IsKeyDown(KEY_D)) squareX += speedX;

        // �������� �� ������������ ����� ������� � ������������
       // �������� �� ������������ ����� ������� � ������������
        if (CheckCollisionRecs(playerRec, obstacleRec)) {
            std::cout << "Collision detected!" << std::endl;
            // ���� �������� ��������� � �������� ����� � ��������� ����, ���������� �������
            if (squareY + squareSize > posY1 && squareX + squareSize > posX1 && squareX < posX1 + 50) {
                squareY = posY1 - squareSize; // ��������� ��������� �� ������� ����� �����
                isJumping = false; // �������� ������ �� � ������
                velocityY = 0; // ������������� �������� �� ��� Y
            }
            if (squareY - squareSize < posY1 && squareX - squareSize < posX1 && squareX > posX1 - 50) {
                squareY = posY1 + squareSize; // ��������� ��������� �� ������� ����� �����
                isJumping = false; // �������� ������ �� � ������
                velocityY = 0; // ������������� �������� �� ��� Y
            }
        }
        // ������ ������ ��� ������� �� ������ (���� �� ������� � ������ ������)
        if (IsKeyPressed(KEY_SPACE) && !isJumping) {
            isJumping = true;
            velocityY = -jumpSpeed; // ��������� �������� ���������� �����
        }

        // ���� ���� ������, �������� ��������� �������� �� ��� Y
        if (isJumping) {
            squareY += velocityY;   // ���������� ������� �� Y
            velocityY += gravity;   // ����������� �������� ���� ��� ��������� ����������

            // ��������, ������ �� ������� ���������� ������
            if (squareY >= screenHeight - squareSize) {
                squareY = screenHeight - squareSize;
                isJumping = false;  // ��������� ������
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // ������������ �������
        DrawRectangle(squareX, squareY, squareSize, squareSize, BLUE);

        DrawRectangle(posX1, posY1, 50, 50, RED); // ������ �����������

        EndDrawing();
    }

    CloseWindow();
    return 0;
}