#include <iostream>


/*! \verbatim embed:rst:leading-asterisk
 * Hello, World!
 * \endverbatim
*/
class SampleClass {
public:
	/*! \verbatim embed:rst:leading-asterisk
	 * This function prints hello
	 * \endverbatim
	 */
	static void printHello();

  /*! \verbatim embed:rst:leading-asterisk
   * This function computes the shader values for a given pixel
   * \endverbatim
   * Here are the function parameters:
   * 
   * \p x: x-coordinate of the pixel
   * 
   * \p y: y-coordinate of the pixel
   * \returns Computed shader value for pixel (x, y)
   */
  static int computeShaders2D(int x, int y);

  /*! \verbatim embed:rst:leading-asterisk
   * This function computes the shader values for a given pixel in 3D.
   * \endverbatim
   * For 2D, use \ref computeShaders2D.
   * Here are the function parameters:
   * 
   * \p x: x-coordinate of the pixel
   * 
   * \p y: y-coordinate of the pixel
   * 
   * \p z: z-coordinate of the pixel
   * \returns Computed shader value for pixel (x, y, z)
   */
  static int computeShaders3D(int x, int y, int z);
};
