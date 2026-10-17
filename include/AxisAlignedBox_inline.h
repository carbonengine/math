// Copyright (c) 2026 CCP Games

#include "Sphere.h"
#include "AxisAlignedEllipsoid.h"
#include "Ray.h"
#include "Vector4.h"


namespace CcpMath
{

inline constexpr AxisAlignedBox::AxisAlignedBox() :
	m_min( FLT_MAX, FLT_MAX, FLT_MAX ),
	m_max( -FLT_MAX, -FLT_MAX, -FLT_MAX )
{
}

inline constexpr AxisAlignedBox::AxisAlignedBox( const Vector3& min, const Vector3& max ) :
	m_min( min ),
	m_max( max )
{
}

inline AxisAlignedBox::AxisAlignedBox( const Vector4& sphere ) :
	m_min( sphere.x - sphere.w, sphere.y - sphere.w, sphere.z - sphere.w ),
	m_max( sphere.x + sphere.w, sphere.y + sphere.w, sphere.z + sphere.w )
{
}

inline AxisAlignedBox::AxisAlignedBox( const Sphere& sphere ) :
	m_min( sphere.center.x - sphere.radius, sphere.center.y - sphere.radius, sphere.center.z - sphere.radius ),
	m_max( sphere.center.x + sphere.radius, sphere.center.y + sphere.radius, sphere.center.z + sphere.radius )
{
}


inline AxisAlignedBox::AxisAlignedBox( const AxisAlignedEllipsoid& ellipsoid ) :
	m_min( ellipsoid.center - ellipsoid.radii ),
	m_max( ellipsoid.center + ellipsoid.radii )
{
}

inline bool AxisAlignedBox::IsInitialized() const
{
	return *this != AxisAlignedBox();
}

inline AxisAlignedBox::operator bool() const
{
	return IsInitialized();
}

inline bool AxisAlignedBox::operator==( const AxisAlignedBox& other ) const
{
	return m_min == other.m_min && m_max == other.m_max;
}

inline bool AxisAlignedBox::operator!=( const AxisAlignedBox& other ) const
{
	return m_min != other.m_min || m_max != other.m_max;
}

inline Vector3 AxisAlignedBox::Size() const
{
	return m_max - m_min;
}

inline Vector3 AxisAlignedBox::Center() const
{
	return ( m_min + m_max ) * 0.5f;
}

inline void AxisAlignedBox::IncludePoint( const Vector3& pos )
{
	m_min = Minimize( m_min, pos );
	m_max = Maximize( m_max, pos );
}

inline void AxisAlignedBox::IncludeBox( const AxisAlignedBox& other )
{
	IncludePoint( other.m_min );
	IncludePoint( other.m_max );
}

inline void AxisAlignedBox::IncludeSphere( const Sphere& sphere )
{
	IncludeBox( AxisAlignedBox( sphere ) );
}

inline void AxisAlignedBox::Include( const Vector3& pos )
{
	IncludePoint( pos );
}

inline void AxisAlignedBox::Include( const AxisAlignedBox& other )
{
	IncludeBox( other );
}

inline void AxisAlignedBox::Include( const Sphere& sphere )
{
	IncludeSphere( sphere );
}

inline bool AxisAlignedBox::IsPointInside( const Vector3& pos ) const
{
	if( ( m_min.x > pos.x ) || ( m_max.x < pos.x ) )
	{
		return false;
	}
	if( ( m_min.y > pos.y ) || ( m_max.y < pos.y ) )
	{
		return false;
	}
	if( ( m_min.z > pos.z ) || ( m_max.z < pos.z ) )
	{
		return false;
	}
	return true;
}

inline bool AxisAlignedBox::Intersects( const AxisAlignedBox& other ) const
{
	return !( m_max.x < other.m_min.x || m_max.y < other.m_min.y || m_max.z < other.m_min.z ||
			  m_min.x > other.m_max.x || m_min.y > other.m_max.y || m_min.z > other.m_max.z );
}

inline void AxisAlignedBox::Offset( const Vector3& by )
{
	m_min += by;
	m_max += by;
}

inline void AxisAlignedBox::Grow( const Vector3& by )
{
	if( !IsInitialized() )
	{
		return;
	}
	m_min -= by;
	m_max += by;
}

inline void AxisAlignedBox::Grow( float by )
{
	if( !IsInitialized() )
	{
		return;
	}
	m_min -= Vector3( by, by, by );
	m_max += Vector3( by, by, by );
}

inline void AxisAlignedBox::Scale( float scale )
{
	if( !IsInitialized() )
	{
		return;
	}
	m_min *= scale;
	m_max *= scale;
}

template <typename T>
inline void AxisAlignedBox::EnumerateVertices( const T& cb ) const
{
	cb( Vector3( m_min.x, m_min.y, m_min.z ) );
	cb( Vector3( m_min.x, m_min.y, m_max.z ) );
	cb( Vector3( m_min.x, m_max.y, m_min.z ) );
	cb( Vector3( m_min.x, m_max.y, m_max.z ) );
	cb( Vector3( m_max.x, m_min.y, m_min.z ) );
	cb( Vector3( m_max.x, m_min.y, m_max.z ) );
	cb( Vector3( m_max.x, m_max.y, m_min.z ) );
	cb( Vector3( m_max.x, m_max.y, m_max.z ) );
}

inline AxisAlignedBox Transform( const AxisAlignedBox& aabb, const Matrix& transform )
{
	AxisAlignedBox b( aabb );
	b.Transform( transform );
	return b;
}

inline AxisAlignedBox Intersection( const AxisAlignedBox& a, const AxisAlignedBox& b )
{
	if( !a.Intersects( b ) )
	{
		return AxisAlignedBox();
	}
	AxisAlignedBox c;
	c.m_min.x = std::max( a.m_min.x, b.m_min.x );
	c.m_min.y = std::max( a.m_min.y, b.m_min.y );
	c.m_min.z = std::max( a.m_min.z, b.m_min.z );
	c.m_max.x = std::min( a.m_max.x, b.m_max.x );
	c.m_max.y = std::min( a.m_max.y, b.m_max.y );
	c.m_max.z = std::min( a.m_max.z, b.m_max.z );
	return c;
}

}
