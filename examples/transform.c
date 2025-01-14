/*
 * Applying transformations to vectors (rotation + translation)
 */

#include "../linalg.h"

int main() {
    Vec4 vec;

	vec = VEC4(-10, 0.7, 27, 1); // Vector to be transformed
  
	printf("=== TRANSLATION ===\n");
	printf("Before:\n");
	laMatPrint(vec);

	Mat4 trans = laMat4GetTranslation(VEC3(79, 419.3, 69393)); // Translation matrix

    vec = laTransformVec4(&trans, &vec); // Apply translation matrix to vector
   
	printf("\nAfter:\n");
	laMatPrint(vec); // Expected [69, 420, 69420, 1]
	
	printf("\n=== ROTATION ===\n");
	vec = laVec4Scale(VEC4_RIGHT, 2, true); // (2, 0, 0)
	
	printf("Before:\n");
	laMatPrint(vec);

	Mat4 rot = laMat4GetRotation(VEC3_UP, deg2rad(45)); // Calculate rotation matrix

	vec = laTransformVec4(&rot, &vec); // Rotate by 45 degrees clockwise

	printf("\nAfter:\n");
	laMatPrint(vec); // Expected [1.4142, 0, -1.4142, 1]

    return 0;
}
