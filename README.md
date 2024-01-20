# Bezier Curve Drawer

This simple C++ project utilizes OpenGL to create an interactive 2D Bezier curve drawing tool. Users can click to add control points, press 'Enter' to complete the curve, and 'c' to clear points. Real-time visualization aids understanding of Bezier curves.

## How to Use

1. **Add Control Points:**
   - Click on the window to add control points.
  
2. **Complete Curve:**
   - Press 'Enter' to finalize the Bezier curve.
  
3. **Clear Control Points:**
   - Press 'c' to clear all control points and start a new curve.

## Dependencies

- OpenGL
- GLUT

## Build and Run

```bash
g++ bezier_curve_drawer.cpp -o bezier_curve_drawer -lGL -lGLU -lglut
./bezier_curve_drawer
```

## Controls

- **Mouse Left-Click:** Add control points.
- **Enter Key:** Complete the curve.
- **'c' Key:** Clear control points.

Enjoy exploring Bezier curves interactively!