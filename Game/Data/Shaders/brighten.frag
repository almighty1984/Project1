uniform sampler2D bgl_RenderedTexture;
    
    void main(void)
    {
        vec4 color = texture2D(bgl_RenderedTexture, gl_TexCoord[0].st);
	 // This line gets the color from the texture that the BGE renders; as the coordinates, it uses
        // the texture coordinate of each pixel in the viewport - gl_TexCoord[0]. I believe gl_TexCoord[1] is the texture coordinates of each pixel 
        // *in the viewport* once scaled to the size of the viewport 
        gl_FragColor = color.gbra;  // This line sets the final color of each pixel (gl_FragColor) to be the color vector, in which r is the red channel,
        // b is the blue, g is the green, and a is the alpha channel. By switching these around, we can manipulate the final color of the screen so that
        // red is now where green should be, blue where green was, and green where red originally is.
    }