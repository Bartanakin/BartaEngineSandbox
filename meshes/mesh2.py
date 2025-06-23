import gmsh
import sys

gmsh.initialize()

geo = gmsh.model.geo
lc = 40

b1 = geo.addPoint(-20, -20, 0, lc)
b2 = geo.addPoint(20, -20, 0, lc)
b3 = geo.addPoint(20, 20, 0, lc)
b4 = geo.addPoint(-20, 20, 0, lc)

n1 = geo.addPoint(-20, -20, 40, lc)
n2 = geo.addPoint(20, -20, 40, lc)
n3 = geo.addPoint(20, 20, 40, lc)
n4 = geo.addPoint(-20, 20, 40, lc)

l1 = geo.addPoint(-80, -20, 40, lc)
l2 = geo.addPoint(-80, -20, 80, lc)
l3 = geo.addPoint(-80, 20, 80, lc)
l4 = geo.addPoint(-80, 20, 40, lc)

r1 = geo.addPoint(80, -20, 40, lc)
r2 = geo.addPoint(80, -20, 80, lc)
r3 = geo.addPoint(80, 20, 80, lc)
r4 = geo.addPoint(80, 20, 40, lc)


lf1 = geo.addLine(b1, b2)
lf2 = geo.addLine(b2, n2)
lf3 = geo.addLine(n2, r1)
lf4 = geo.addLine(r1, r2)
lf5 = geo.addLine(r2, l2)
lf6 = geo.addLine(l2, l1)
lf7 = geo.addLine(l1, n1)
lf8 = geo.addLine(n1, b1)

lb1 = geo.addLine(b3, b4)
lb2 = geo.addLine(n3, b3)
lb3 = geo.addLine(r4, n3)
lb4 = geo.addLine(r3, r4)
lb5 = geo.addLine(l3, r3)
lb6 = geo.addLine(l4, l3)
lb7 = geo.addLine(n4, l4)
lb8 = geo.addLine(b4, n4)

ld1 = geo.addLine(b2, b3)
ld2 = geo.addLine(b4, b1)

ll1 = geo.addLine(l4, l1)
ll2 = geo.addLine(l2, l3)

lr1 = geo.addLine(r1, r4)
lr2 = geo.addLine(r3, r2)

ln1 = geo.addLine(n3, n2)
ln2 = geo.addLine(n1, n4)


front_loop = geo.addCurveLoop([lf1, lf2, lf3, lf4, lf5, lf6, lf7, lf8])
back_loop = geo.addCurveLoop([lb8, lb7, lb6, lb5, lb4, lb3, lb2, lb1])
down_loop = geo.addCurveLoop([lf1, ld1, lb1, ld2])
down_left_loop = geo.addCurveLoop([lf7, ln2, lb7, ll1])
down_right_loop = geo.addCurveLoop([lf3, lr1, lb3, ln1])
top_loop = geo.addCurveLoop([lf5, ll2, lb5, lr2])
left_outer_loop = geo.addCurveLoop([lf4, -lr2, lb4, -lr1])
right_outer_loop = geo.addCurveLoop([lf6, -ll1, lb6, -ll2])
left_inner_loop = geo.addCurveLoop([lf8, -ld2, lb8, -ln2])
right_inner_loop = geo.addCurveLoop([lf2, -ln1, lb2, -ld1])

front_surface = geo.addPlaneSurface([front_loop], tag=666)
back_surface = geo.addPlaneSurface([back_loop], tag=667)
down_surface = geo.addPlaneSurface([down_loop], tag=668)
down_left_surface = geo.addPlaneSurface([down_left_loop], tag=669)
down_right_surface = geo.addPlaneSurface([down_right_loop], tag=670)
top_surface = geo.addPlaneSurface([top_loop], tag=671)
left_outer_surface = geo.addPlaneSurface([left_outer_loop], tag=672)
right_outer_surface = geo.addPlaneSurface([right_outer_loop], tag=673)
left_inner_surface = geo.addPlaneSurface([left_inner_loop], tag=674)
right_inner_surface = geo.addPlaneSurface([right_inner_loop], tag=6675)

dirichlet_group = gmsh.model.addPhysicalGroup(2, [down_surface], tag=100)
gmsh.model.setPhysicalName(2, dirichlet_group, "DirichletCondition")


sl = geo.addSurfaceLoop([
    front_surface,
    back_surface,
    down_surface,
    down_left_surface,
    down_right_surface,
    top_surface,
    left_outer_surface,
    right_outer_surface,
    left_inner_surface,
    right_inner_surface
])

geo.addVolume([sl])

geo.synchronize()

gmsh.model.mesh.generate(3)
gmsh.option.setNumber("Mesh.SaveAll", 1)
gmsh.write("gmsh_T.msh")


# Optionally launch GUI to view it
if '-nopopup' not in sys.argv:
    gmsh.fltk.run()

gmsh.finalize()