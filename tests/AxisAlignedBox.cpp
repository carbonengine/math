// Copyright (c) 2026 CCP Games

#include "gtest/gtest.h"
#include "CcpMath.h"

using CcpMath::AxisAlignedBox;

TEST( AxisAlignedBoxTest, IntersectsBox )
{
	AxisAlignedBox a( Vector3( 0.f, 0.f, 0.f ), Vector3( 1.f, 1.f, 1.f ) );
	AxisAlignedBox overlapping( Vector3( 0.5f, 0.5f, 0.5f ), Vector3( 2.f, 2.f, 2.f ) );
	AxisAlignedBox contained( Vector3( 0.25f, 0.25f, 0.25f ), Vector3( 0.75f, 0.75f, 0.75f ) );
	AxisAlignedBox touching( Vector3( 1.f, 0.f, 0.f ), Vector3( 2.f, 1.f, 1.f ) );
	AxisAlignedBox disjoint( Vector3( 5.f, 5.f, 5.f ), Vector3( 6.f, 6.f, 6.f ) );
	AxisAlignedBox disjointOnOneAxis( Vector3( 0.f, 0.f, 2.f ), Vector3( 1.f, 1.f, 3.f ) );

	EXPECT_TRUE( a.Intersects( a ) );
	EXPECT_TRUE( a.Intersects( overlapping ) );
	EXPECT_TRUE( overlapping.Intersects( a ) );
	EXPECT_TRUE( a.Intersects( contained ) );
	EXPECT_TRUE( contained.Intersects( a ) );
	EXPECT_TRUE( a.Intersects( touching ) );

	EXPECT_FALSE( a.Intersects( disjoint ) );
	EXPECT_FALSE( disjoint.Intersects( a ) );
	EXPECT_FALSE( a.Intersects( disjointOnOneAxis ) );
	EXPECT_FALSE( disjointOnOneAxis.Intersects( a ) );
}

TEST( AxisAlignedBoxTest, Intersection )
{
	AxisAlignedBox a( Vector3( 0.f, 0.f, 0.f ), Vector3( 1.f, 1.f, 1.f ) );
	AxisAlignedBox b( Vector3( 0.5f, -1.f, 0.25f ), Vector3( 2.f, 0.5f, 0.75f ) );

	AxisAlignedBox c = CcpMath::Intersection( a, b );
	EXPECT_EQ( Vector3( 0.5f, 0.f, 0.25f ), c.m_min );
	EXPECT_EQ( Vector3( 1.f, 0.5f, 0.75f ), c.m_max );

	AxisAlignedBox disjoint( Vector3( 5.f, 5.f, 5.f ), Vector3( 6.f, 6.f, 6.f ) );
	EXPECT_FALSE( CcpMath::Intersection( a, disjoint ).IsInitialized() );
}
