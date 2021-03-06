#version 410
    layout(location = 0) in vec2 inPosition;
    layout(location = 1) in vec4 inColor;
    uniform vec2 translation;
    uniform float scale;
    uniform float rotation;
    out vec4 fragColor;
    void main() {
        float sinAngle = sin(rotation);
        float cosAngle = cos(rotation);
      vec2 newPosition = vec2(
          inPosition.x * cosAngle - inPosition.y * sinAngle,
          inPosition.x * sinAngle + inPosition.y * cosAngle
      ); 
      newPosition = newPosition * scale + translation;
      gl_Position = vec4(newPosition, 0, 1);
      fragColor = inColor;
    }