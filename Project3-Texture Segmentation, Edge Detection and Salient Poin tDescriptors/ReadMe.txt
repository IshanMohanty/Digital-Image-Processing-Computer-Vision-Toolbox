/* EE 569
   ISHAN MOHANTY
   USC ID : 4461 3447 18
*/




Installation:
Unzip source code zip file at a location.
make clean && make.  /* Compiles all files */


For Testing:

/*Go to CD bin */

cd bin/

Example :


                          <input image> <outputimage1> <width> <height> <other parameters>
./shrink                  <input image> <outputimage1> <width> <height> <other parameters>
./thin                    <input image> <outputimage1> <width> <height> <other parameters>
./skel                    <input image> <outputimage1> <width> <height> <other parameters>
./count 			      <input image> <outputimage1> <width> <height> <other parameters>
./unique_count            <input image> <outputimage1> <width> <height> <other parameters>
./dither                  <input image> <outputimage1> <width> <height> <other parameters>
./fourleveldither         <input image> <outputimage1> <width> <height> <other parameters>
./errordiffusion          <input image> <outputimage1> <width> <height> <other parameters>
./separableDiff           <input image> <outputimage1> <width> <height> <other parameters>
./MBVQ                    <input image> <outputimage1> <width> <height> <other parameters>
./warp                    <input image> <outputimage1> <width> <height> <other parameters>
./homography              <input image> <outputimage1> <width> <height> <other parameters>


specific example:

usage : ./warp <input_image.raw> <warped_output_image.raw> <dewarped_image.raw> <width> <height>

else just go to bin and run ./warp , you will get a prompt with the syntax to be given

example : 
./warp

Syntax Error - Incorrect Parameter Usage:
./a.out  input_image.raw output_image.raw dewarped_image.raw width height
