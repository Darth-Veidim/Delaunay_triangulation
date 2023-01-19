---
type: slide
slideOptions:
transition: slide
width: 1400
height: 900
margin: 0.1
---

<style>
  .reveal strong {
    font-weight: bold;
    color: orange;
  }
  .reveal p {
    text-align: left;
  }
  .reveal section h1 {
    color: orange;
  }
  .reveal section h2 {
    color: orange;
  }
  .reveal code {
    font-family: 'Ubuntu Mono',serif;
    color: orange;
  }
  .reveal section img {
    background:none;
    border:none;
    box-shadow:none;
  }
</style>

# Delaunay Triangulation

---

## What is Delaunay Triangulation

The Delaunay Triangulation defines an optimal form for organizing
unstructured or semi-random sample points into a triangular mesh. 
That optimality makes the Delaunay Triangulation a useful tool for 
interpolation, grid construction, and surface analysis.

<img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig1.png" title="non-optimal_and_optimal" width="600"/>

---
## Optimality criterion

A triangulation is "Delaunay optimal" if and only if the following 
conditions are met:
 1. All triangles formed by the mesh are non-degenerate.

<img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig2.png" title="degenerate_and_non-degenerate_triangle" width="200"/>

---

 2. All triangles in the mesh produce a circumcircle which does 
    not contain any other vertices from the mesh except for the 
    three vertices that define the triangle.

<img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig3.png" title="good_triangle" width="600"/>

Here, triangle ABC is a <span style="color:green"> _**good**_ 
</span> triangle. As well as triangle CBD. Which means that 
triangulation, consisting of two triangles is Delaunay optimal.

---

If the second rule is violated we call such triangles
<span style="color:red"> _**bad**_ </span>. 

<img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig4.png" title="bad_triangle" width="600"/>

Circumcercle of the triangle ABC _contains_ point D, as well as 
circumcercle of triangle CDB _contains_ point A meaning that they 
are bad triangles.

---

## Restoring Delaunay Optimality

In the figure above, the edge CB seems to be the source of the 
problem. We can break the link between vertices C and B and 
instead create an edge between A to D.

<img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig5.png" title="good_to_bad" width="600"/>

The operation that switches the common edge between two adjacent
triangles is sometimes called a "flip".

<img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig8.gif" title="flip" width="350"/>

If the Delaunay criterion is satisfied everywhere on the TIN, the 
minimum interior angle of all triangles is maximized

---

## Applications

- Mesh generation

 <img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig6.png" title="triangulat_mesh" width="200"/>

- Euclidean minimum spanning tree<sup>1</sup>

 <img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig7.png" title="EMST" width="200"/>

<sup>1</sup>_(an EMST connects a set of dots using lines such that the total length of all the lines is minimized and any dot can be reached from any other by following the lines.)_

---

- Triangulated irregular network (TIN)

 <img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig9.gif" title="TIN" width="400"/>

- Path finding

 <img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig10.png" title="path_finding" width="600"/>

---

## Algorithms

- Flip algorithms (their convergence is not guaranteed for n>2 
  dimensions)
- Incremental (Bowyer–Watson algorithm _O(n<sup>2</sup>)_)
- Divide and conquer (DeWall _O(n log n)_)

---

### Divide and conquer: DeWall (1/2)

<img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig13-0.png" title="DeWall_1" width="600"/>

---

### Divide and conquer: DeWall (2/2)

<img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig13-1.png" title="DeWall_2" width="600"/>

---

## Implementation

<img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig11-0.png" title="algo1" width="400"/>
<img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig11-1.png" title="algo2" width="400"/>

<img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig11-2.png" title="algo3" width="400"/>
<img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig11-3.png" title="algo4" width="400"/>

<img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig11-4.png" title="algo5" width="400"/>
<img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig11-5.png" title="algo6" width="400"/>

---

## Optimality

<img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig12-0.png" title="optim0" width="400"/>
<img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig12-1.png" title="optim1" width="400"/>
<img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig12-2.png" title="optim2" width="400"/>
<img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig12-3.png" title="optim3" width="400"/>
<img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig12-4.png" title="optim4" width="400"/>
<img src="C:\Users\gally\OneDrive - bwedu\3_semester\Implementation of Algoritms for Finite Elements\Summer_seminar\figs\fig12-5.png" title="optim5" width="400"/>


### References

- [Cartography Playground](https://cartography-playground.gitlab.io/playgrounds/triangulation-delaunay-voronoi-diagram/)
- [Tinfour Software Project Documentation](https://gwlucastrig.github.io/TinfourDocs/DelaunayIntro/index.html)
- [Formula Student: Automated driving with Delaunay triangulation](https://blogs.mathworks.com/student-lounge/2022/10/03/path-planning-for-formula-student-driverless-cars-using-delaunay-triangulation/)
- [Wikipedia: Delaunay Triangulation](https://en.wikipedia.org/wiki/Delaunay_triangulation#:~:text=Delaunay%20triangulations%20are%20often%20used,triangulation%20algorithms%20have%20been%20developed.)