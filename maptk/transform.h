/*ckwg +29
 * Copyright 2014-2015 by Kitware, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  * Neither name of Kitware, Inc. nor the names of any contributors may be used
 *    to endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \file
 * \brief Header for maptk::transform functions
 */

#ifndef MAPTK_TRANSFORM_H_
#define MAPTK_TRANSFORM_H_

#include <maptk/config.h>
#include <maptk/camera.h>

#include <vital/types/similarity.h>
#include <vital/types/covariance.h>
#include <vital/types/camera_map.h>
#include <vital/types/landmark_map.h>


namespace kwiver {
namespace maptk {


/// Transform a 3D covariance matrix with a similarity transformation
/**
 *  This function applies the scale and rotation of a similarity transformation
 *  to a covariance matrix such that the Mahalanobis distance measure between
 *  two points remains unchanged after applying the same transformation to the
 *  points.  That is,
 *       (x1-m1)'*C1*(x1-m1) == (x2-m2)'*C2*(x2-m2)
 *       for x2 = xform*x1 and m2 = xform*m1 and C2 = transform(C1, xform)
 *
 *  \param [in] covar the 3D covariance to transform
 *  \param [in] xform the 3D similarity transformation to apply
 *  \return a 3D covariance transformed by the similarity transformation
 */
template <typename T>
MAPTK_LIB_EXPORT
vital::covariance_<3,T> transform(const vital::covariance_<3,T>& covar,
                                  const vital::similarity_<T>& xform);


/// Transform the camera by applying a similarity transformation in place
MAPTK_LIB_EXPORT
void transform_inplace(const vital::similarity_d& xform,
                       vital::simple_camera& cam);


/// Transform the landmark by applying a similarity transformation in place
template <typename T>
MAPTK_LIB_EXPORT
void transform_inplace(const vital::similarity_<T>& xform,
                       vital::landmark_<T>& lm);


/// construct a transformed camera by applying a similarity transformation
MAPTK_LIB_EXPORT
vital::camera_sptr transform(vital::camera_sptr cam,
                             const vital::similarity_d& xform);


/// construct a transformed map of cameras by applying a similarity transformation
MAPTK_LIB_EXPORT
vital::camera_map_sptr transform(vital::camera_map_sptr cameras,
                                 const vital::similarity_d& xform);


/// construct a transformed landmark by applying a similarity transformation
MAPTK_LIB_EXPORT
vital::landmark_sptr transform(vital::landmark_sptr lm,
                               const vital::similarity_d& xform);


/// construct a transformed map of landmarks by applying a similarity transformation
MAPTK_LIB_EXPORT
vital::landmark_map_sptr transform(vital::landmark_map_sptr landmarks,
                                   const vital::similarity_d& xform);


/// Estimate a canonical coordinate transform for landmarks and cameras
/**
 * Center landmarks about the origin with unit average scale,
 * orient the average camera principal axis to the -Z axis and
 * the average camera up vector to Y axis.
 * \note This assumes most cameras are viewing from the same side of
 *       3D landmarks and have similar up directions.
 */
MAPTK_LIB_EXPORT
vital::similarity_d
canonical_transform(vital::camera_map_sptr cameras,
                    vital::landmark_map_sptr landmarks);

} // end namespace maptk
} // end namespace kwiver


#endif // MAPTK_TRANSFORM_H_
