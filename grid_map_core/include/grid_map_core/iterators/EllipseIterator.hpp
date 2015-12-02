/*
 * EllipseIterator.hpp
 *
 *  Created on: Dec 2, 2015
 *      Author: Péter Fankhauser
 *   Institute: ETH Zurich, Autonomous Systems Lab
 */

#pragma once

#include "grid_map_core/GridMap.hpp"
#include "grid_map_core/iterators/SubmapIterator.hpp"

// Eigen
#include <Eigen/Core>

// unique_ptr
#include <memory>

namespace grid_map {

/*!
 * Iterator class to iterate through a ellipsoid area of the map.
 * The main axis of the ellipse are aligned with the map frame.
 */
class EllipseIterator
{
public:

  /*!
   * Constructor.
   * @param gridMap the grid map to iterate on.
   * @param center the position of the ellipse center.
   * @param length the length of the main axis.
   */
  EllipseIterator(const GridMap& gridMap, const Position& center, const Length& length);

  /*!
   * Assignment operator.
   * @param iterator the iterator to copy data from.
   * @return a reference to *this.
   */
  EllipseIterator& operator =(const EllipseIterator& other);

  /*!
   * Compare to another iterator.
   * @return whether the current iterator points to a different address than the other one.
   */
  bool operator !=(const EllipseIterator& other) const;

  /*!
   * Dereference the iterator with const.
   * @return the value to which the iterator is pointing.
   */
  const Index& operator *() const;

  /*!
   * Increase the iterator to the next element.
   * @return a reference to the updated iterator.
   */
  EllipseIterator& operator ++();

  /*!
   * Indicates if iterator is past end.
   * @return true if iterator is out of scope, false if end has not been reached.
   */
  bool isPastEnd() const;

private:

  /*!
   * Check if current index is inside the ellipse.
   * @return true if inside, false otherwise.
   */
  bool isInside();

  /*!
   * Finds the submap that fully contains the ellipse and returns the parameters.
   * @param[in] center the position of the ellipse center.
   * @param[in] length the length of the main axis.
   * @param[out] startIndex the start index of the submap.
   * @param[out] bufferSize the buffer size of the submap.
   */
  void findSubmapParameters(const Position& center, const Length& length,
                            Index& startIndex, Size& bufferSize) const;

  //! Position of the circle center;
  Position center_;

  //! Length of the main axis.
  Length length_;
  Length lengthSquare_;

  //! Grid submap iterator.
  std::shared_ptr<SubmapIterator> internalIterator_;

  //! Map information needed to get position from iterator.
  Length mapLength_;
  Position mapPosition_;
  double resolution_;
  Size bufferSize_;
  Index bufferStartIndex_;
};

} /* namespace */
