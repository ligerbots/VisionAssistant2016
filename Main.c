////////////////////////////////////////////////////////////////////////////////
//
// Author : Vision Assistant
// Purpose: This file implements the algorithm prototyped in Vision Assistant.
//
// WARNING: This file was automatically generated.
//          Any changes you make to this file will be lost if you generate the
//          file again.
//
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
//     Includes
//==============================================================================

#include <stdio.h>
#include <nivision.h>
#include <windows.h>
#include "ImageProcessing.h"


//==============================================================================
//  Defines
//==============================================================================

#define DISPLAY_WINDOW 0


//==============================================================================
//  Main Function
//==============================================================================

int main (int argc, char *argv[])
{
    int success = 1;
    int err = 0;
    char** imagePath;       // Image Path
    int cancelled;
    ImageType imageType;    // Image Type
    Image* image;           // Image


    // IMAQ Vision creates windows in a separate thread
    imaqSetWindowThreadPolicy(IMAQ_SEPARATE_THREAD);

    // Display the Load Image dialog
    imagePath = imaqLoadImagePopup(NULL, "*.*", NULL, "Open Image", FALSE, IMAQ_BUTTON_LOAD, 0, 0, 1, 0, &cancelled, NULL);

	if (!cancelled)
	{
		// Get the type of the image file to create an image of the right type
		imaqGetFileInfo(imagePath[0], NULL, NULL, NULL, NULL, NULL, &imageType);

		// Create an IMAQ Vision image
		image = imaqCreateImage(imageType, 7);

		// Read the image from disk
		imaqReadFile(image, imagePath[0], NULL, NULL);

		// Vision Assistant Algorithm
		success = IVA_ProcessImage(image);
		if (!success)
			err = imaqGetLastError();

		// Display the image
		imaqMoveWindow(DISPLAY_WINDOW, imaqMakePoint(0, 0));
		imaqSetWindowPalette(DISPLAY_WINDOW, IMAQ_PALETTE_BINARY, NULL, 0);
		int width, height;
		//RGBValue color = IMAQ_RGB_YELLOW;
		imaqGetImageSize(image, &width, &height);
		Rect rect = { height / 3, width / 3, height / 3, width / 3 };
		//imaqOverlayOval(image, rect, &color, IMAQ_DRAW_VALUE, NULL);5
		for (float xcolor = (float)1.0; xcolor < (float)1.0e9; xcolor *= (float)10.0) {
			printf("Color is %5.3f. Hit enter to see the next color\n", xcolor);
			imaqDrawShapeOnImage(image, image, rect, IMAQ_DRAW_VALUE, IMAQ_SHAPE_OVAL, xcolor);
			imaqDisplayImage(image, DISPLAY_WINDOW, TRUE);
			getchar();
		}

        // Wait for a key press before exiting
        printf ("Press Enter to exit.\n");
        getchar();
        // Dispose resources
        imaqDispose(image);
    }

    imaqDispose(imagePath);

    return 0;
}
