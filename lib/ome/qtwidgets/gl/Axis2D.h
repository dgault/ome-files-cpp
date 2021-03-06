/*
 * #%L
 * OME-QTWIDGETS C++ library for display of Bio-Formats pixel data and metadata.
 * %%
 * Copyright © 2014 - 2015 Open Microscopy Environment:
 *   - Massachusetts Institute of Technology
 *   - National Institutes of Health
 *   - University of Dundee
 *   - Board of Regents of the University of Wisconsin-Madison
 *   - Glencoe Software, Inc.
 * %%
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are
 * those of the authors and should not be interpreted as representing official
 * policies, either expressed or implied, of any organization.
 * #L%
 */

#ifndef OME_QTWIDGETS_GL_AXIS2D_H
#define OME_QTWIDGETS_GL_AXIS2D_H

#include <QtCore/QObject>
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLShader>
#include <QtGui/QOpenGLFunctions>

#include <ome/bioformats/Types.h>
#include <ome/bioformats/FormatReader.h>

#include <ome/compat/memory.h>

#include <ome/qtwidgets/glm.h>
#include <ome/qtwidgets/glsl/v110/GLFlatShader2D.h>

namespace ome
{
  namespace qtwidgets
  {
    namespace gl
    {

      /**
       * 2D (xy) axis renderer.
       *
       * Draws x and y axes for the specified image.
       */
      class Axis2D : public QObject, protected QOpenGLFunctions
      {
        Q_OBJECT

      public:
        /**
         * Create a 2D axis.
         *
         * The size and position will be taken from the specified image.
         *
         * @param reader the image reader.
         * @param series the image series.
         * @param parent the parent of this object.
         */
        explicit Axis2D(ome::compat::shared_ptr<ome::bioformats::FormatReader>  reader,
                        ome::bioformats::dimension_size_type                    series,
                        QObject                                                *parent = 0);

        /// Destructor.
        virtual
        ~Axis2D() = 0;

        /**
         * Create GL buffers.
         *
         * @note Requires a valid GL context.  Must be called before
         * rendering.
         */
        virtual
        void
        create();

        /**
         * Render the axis.
         *
         * @param mvp the model view projection matrix.
         */
        virtual
        void
        render(const glm::mat4& mvp) = 0;

      protected:
        /**
         * Set the size of the x and y axes.
         *
         * @param xlim the x axis limits (range).
         * @param ylim the y axis limits (range).
         * @param soff shaft offset (x and y offsets from midline).
         * @param slim the axis shaft width (min and max from midline).
         */
        virtual
        void
        setSize(glm::vec2 xlim,
                glm::vec2 ylim,
                glm::vec2 soff,
                glm::vec2 slim);

        /// The vertices for the x axis.
        QOpenGLBuffer xaxis_vertices;
        /// The vertices for the y axis.
        QOpenGLBuffer yaxis_vertices;
        /// The elements for both axes.
        QOpenGLBuffer axis_elements;
        /// The image reader.
        ome::compat::shared_ptr<ome::bioformats::FormatReader> reader;
        /// The image series.
        ome::bioformats::dimension_size_type series;
      };

    }
  }
}

#endif // OME_QTWIDGETS_GL_AXIS2D_H

/*
 * Local Variables:
 * mode:C++
 * End:
 */
