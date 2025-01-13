/*
 * Applying transformations to vectors (rotation + translation)
 */

#include "../linalg.h"

int main() {
    srand(time(NULL));

    Vec4 a = VEC4(0, 0, 0, 1);
    Mat4 trans = laMat4GetTranslation(VEC3(69, 420, 21));
    Vec4 res = laVec4Empty;
    laMatMul(a, trans, res);
    laMatPrint(trans);
    laMatPrint(res);

	/*Vec3 R = VEC3(0, 1, 1);
    laVecNormalize(R);

    printf("Rotation axis:\n");
    laMatPrint(R);

    Mat4 rotation_mat = laMat4GetRotation(R, deg2rad(90.0f));

    printf("\nRotation matrix:\n");
    laMatPrint(rotation_mat);

    Mat4 transl_mat = laMat4GetTranslation(VEC3(5.0f, 0.69f, 4.20f));

    printf("\nTranslation matrix:\n");
    laMatPrint(transl_mat);

    Mat4 trans_mat = laMat4Empty;
    laMatMul(rotation_mat, transl_mat, trans_mat);

    printf("\nTransform matrix:\n");
    laMatPrint(trans_mat);

    Vec4 vec = VEC4(1, 1, 1, 1);
    
    printf("\nVector before transform:\n");
    laMatPrint(vec);

    Vec4 new_vec = laVec4Empty;

    laMatMul(trans_mat, vec, new_vec); // Note: laMatMul(trans_mat, vec, vec) does not work since the 3rd parameter is updated in real-time

    printf("\nVector after transform:\n");
    laMatPrint(new_vec);*/

    return 0;
}
