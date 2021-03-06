// BeginLicense:
// Part of: xcsg - XML based Constructive Solid Geometry
// Copyright (C) 2017-2020 Carsten Arnholm
// All rights reserved
//
// This file may be used under the terms of either the GNU General
// Public License version 2 or 3 (at your option) as published by the
// Free Software Foundation and appearing in the files LICENSE.GPL2
// and LICENSE.GPL3 included in the packaging of this file.
//
// This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
// INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE. ALL COPIES OF THIS FILE MUST INCLUDE THIS LICENSE.
// EndLicense:

#include "xspline_path.h"
#include "csg_parser/cf_xmlNode.h"
#include "mesh_utils.h"

xspline_path::xspline_path()
{}

xspline_path::xspline_path(const cf_xmlNode& const_node)
{
   if(const_node.tag() != "spline_path")throw logic_error("Expected xml tag spline_path, but found " + const_node.tag());

   m_cp.reserve(500);

   cf_xmlNode node = const_node;
   for(auto i=node.begin(); i!=node.end(); i++) {

      cf_xmlNode sub(i);
      if("cpoint" == sub.tag()) {
         double px = sub.get_property("x",0.0);
         double py = sub.get_property("y",0.0);
         double pz = sub.get_property("z",0.0);
         double vx = sub.get_property("vx",0.0);
         double vy = sub.get_property("vy",0.0);
         double vz = sub.get_property("vz",0.0);

         csplines::cpoint cp(px,py,pz,vx,vy,vz);
         if(cp.length() > 0.0) m_cp.push_back(cp);
         else throw logic_error("spline_path: control point 'up' vector length must be > 0.0");

         size_t ncp = m_cp.size();
         if(ncp > 1) {
            const csplines::cpoint& cp_prev = m_cp[ncp-2];
            double dist = cp.dist(cp_prev);
            if(dist < fabs(mesh_utils::secant_tolerance())) {
               throw logic_error("spline_path: Neighbour control points too close to each other: " + std::to_string(dist));
            }
         }
      }
   }
   m_cp.shrink_to_fit();

   if(m_cp.size() < 2)throw logic_error("spline_path: at least 2 <cpoint> control points must be specified.");
}

xspline_path::~xspline_path()
{}


const std::vector<csplines::cpoint>& xspline_path::cp() const
{
   return m_cp;
}
