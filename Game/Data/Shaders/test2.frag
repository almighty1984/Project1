uniform sampler2D bgl_RenderedTexture;

void main(void) {

        vec2 p = gl_FragCoord.xy*2. - resolution;

        float a = floor(degrees(4. + atan(p.y, p.x))*2.) / 4.;

        float d = pow(2., -10.*fract(0.1*time*(h(a + .5)*-.1 - .1) - h(a)*1000.));

        if (abs(length(p) - d*length(resolution)) < d*35.) {
                gl_FragColor = vec4(d*(h(a + .5)*3.));
        }
        else {
                gl_FragColor = vec4(0.);
        }
}