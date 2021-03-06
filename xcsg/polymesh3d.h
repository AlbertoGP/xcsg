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

#ifndef POLYMESH3D_H
#define POLYMESH3D_H

#include "xshape.h"
#include <vector>
#include "clipper_csg/polymesh2d.h"
#include <carve/matrix.hpp>

class polymesh3d {
public:
   typedef std::vector<xvertex>       vertex_vector;
   typedef std::vector<size_t>        index_vector;    // a vector of indices into m_vert
   typedef std::vector<index_vector>  face_vector;     // an index_vector per face
   typedef std::vector<index_vector>  contour_vector;  // an index_vector per contour

   polymesh3d();

   // transform the 2d mesh into 3d
   polymesh3d(std::shared_ptr<const polymesh2d> pm2d, const carve::math::Matrix& t = carve::math::Matrix());

   virtual ~polymesh3d();

   // return number of vertices
   size_t nvertices() const;

   // return vertex coordinates for given vertex
   const xvertex& vertex(size_t ivertex) const;

   // return number of faces
   size_t nfaces() const;

   // return vertex index vector for given face
   const index_vector& face(size_t iface) const;

   // return number of contours
   size_t ncontours() const;

   // return vertex index vector for given contour
   const index_vector& contour(size_t icontour) const;

private:
   vertex_vector   m_vert;    // vertices
   face_vector     m_face;    // faces    , each entry contains N indices into m_vert (not limited to 3)
   contour_vector  m_contour; // contours , each entry contains N indices into m_vert
};

#endif // POLYMESH3D_H
