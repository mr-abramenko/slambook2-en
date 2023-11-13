#include <cmath>
#include <iostream>

using namespace std;

#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace Eigen;

// This program demonstrates the use of Eigen geometry module

int main(int argc, char **argv) {
  // The Eigen/Geometry module provides various rotation and translation
  // representations 3D rotation matrix directly uses Matrix3d or Matrix3f
  Matrix3d rotation_matrix = Matrix3d::Identity();
  // Rotation vector uses AngleAxis,
  // Its bottom layer is not directly a Matrix, but the operation can be treated
  // as a matrix (because the operator is overloaded)
  AngleAxisd rotation_vector(M_PI / 4, Vector3d(0, 0, 1));  // Rotate 45 degrees
                                                            // along the Z axis
  cout.precision(3);
  cout << "rotation matrix =\n"
       << rotation_vector.matrix() << endl;  // Convert to matrix using matrix()

  // You can also assign values directly
  rotation_matrix = rotation_vector.toRotationMatrix();
  // Use AngleAxis to perform coordinate transformation
  Vector3d v(1, 0, 0);
  Vector3d v_rotated = rotation_vector * v;
  cout << "(1,0,0) after rotation (by angle axis) = " << v_rotated.transpose()
       << endl;
  // Or use rotation matrix
  v_rotated = rotation_matrix * v;
  cout << "(1,0,0) after rotation (by matrix) = " << v_rotated.transpose()
       << endl;

  // Euler angles: The rotation matrix can be directly converted into Euler
  // angles
  Vector3d euler_angles = rotation_matrix.eulerAngles(
      2, 1, 0);  // ZYX order, that is, yaw - pitch - roll order
  cout << "yaw pitch roll = " << euler_angles.transpose() << endl;

  // Euclidean transformation matrix uses Eigen::Isometry
  Isometry3d T = Isometry3d::Identity();  // Although it is called 3d, it is
                                          // actually a 4*4 matrix
  T.rotate(rotation_vector);              // Rotate according to rotation_vector
  T.pretranslate(Vector3d(1, 3, 4));  // Set the translation vector to (1,3,4)
  cout << "Transform matrix = \n" << T.matrix() << endl;

  // Use transformation matrix to perform coordinate transformation
  Vector3d v_transformed = T * v;  // Equivalent to R*v+t
  cout << "v tranformed = " << v_transformed.transpose() << endl;

  // For affine and projective transformations, use Eigen::Affine3d and
  // Eigen::Projective3d, omitted

  // Quaternion
  // You can directly assign AngleAxis to quaternion and vice versa
  Quaterniond q = Quaterniond(rotation_vector);
  cout << "quaternion from rotation vector = " << q.coeffs().transpose()
       << endl;  // Please note that the order of coeffs is (x, y, z, w), w is
                 // the real part, and the first three are the imaginary part
                 // You can also assign the rotation matrix to it
  q = Quaterniond(rotation_matrix);
  cout << "quaternion from rotation matrix = " << q.coeffs().transpose()
       << endl;
  // Use quaternion to rotate a vector, just use overloaded multiplication
  v_rotated = q * v;  // 注意数学上是qvq^{-1}
  cout << "(1,0,0) after rotation = " << v_rotated.transpose() << endl;
  // Expressed by regular vector multiplication, it should be calculated as
  // follows
  cout << "should be equal to "
       << (q * Quaterniond(0, 1, 0, 0) * q.inverse()).coeffs().transpose()
       << endl;

  return 0;
}
