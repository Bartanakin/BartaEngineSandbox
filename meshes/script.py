import gmsh
import sys

gmsh.initialize()

geo = gmsh.model.geo
lc = 40

p2 = geo.addPoint(0, 0, 60, lc)
p3 = geo.addPoint(-20, -20, 0, lc)
p4 = geo.addPoint(20, -20, 0, lc)
p5 = geo.addPoint(20, 20, 0, lc)
p6 = geo.addPoint(-20, 20, 0, lc)

l1u = geo.addLine(p2, p3)
l2u = geo.addLine(p2, p4)
l3u = geo.addLine(p2, p5)
l4u = geo.addLine(p2, p6)

l1b = geo.addLine(p3, p4)
l2b = geo.addLine(p4, p5)
l3b = geo.addLine(p5, p6)
l4b = geo.addLine(p6, p3)

loop1 = geo.addCurveLoop([l1u, l1b, -l2u])
loop2 = geo.addCurveLoop([l2u, l2b, -l3u])
loop3 = geo.addCurveLoop([l3u, l3b, -l4u])
loop4 = geo.addCurveLoop([l4u, l4b, -l1u])
loop_bottom = geo.addCurveLoop([l1b, l2b, l3b, l4b])

surface1 = geo.addPlaneSurface([loop1], tag=666)
surface2 = geo.addPlaneSurface([loop2], tag=555)
surface3 = geo.addPlaneSurface([loop3], tag=444)
surface4 = geo.addPlaneSurface([loop4], tag=333)
surface_bottom = geo.addPlaneSurface([loop_bottom], tag=222)

dirichlet_group = gmsh.model.addPhysicalGroup(2, [surface_bottom], tag=100)
gmsh.model.setPhysicalName(2, dirichlet_group, "DirichletCondition")


sl = geo.addSurfaceLoop([surface1, surface2, surface3, surface4, surface_bottom])

geo.addVolume([sl])

geo.synchronize()

gmsh.model.mesh.generate(3)
gmsh.option.setNumber("Mesh.SaveAll", 1)
gmsh.write("gmsh_example.msh")


# Optionally launch GUI to view it
if '-nopopup' not in sys.argv:
    gmsh.fltk.run()

gmsh.finalize()