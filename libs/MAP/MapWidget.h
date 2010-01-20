/* Copyright (C) 2010 Mobile Sorcery AB

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.
*/

#ifndef MAPWIDGET_H_
#define MAPWIDGET_H_

#include <ma.h>
#include <MAUI/Widget.h>
#include <MAUtil/environment.h>
#include <MAUI/Font.h>

#include "LonLat.h"
#include "MapCache.h"

using namespace MAUI;

namespace MAP
{
	class MapTile;
	class MapSource;
	class MapCache;
	class MapWidget;

	//=========================================================================
	enum MapWidgetScrollDirection
	//=========================================================================
	{
		SCROLLDIRECTION_NORTH,
		SCROLLDIRECTION_SOUTH,
		SCROLLDIRECTION_EAST,
		SCROLLDIRECTION_WEST
	};

	//=========================================================================
	//
	// Basic map display widget.
	// No user interaction at this level.
	//
	class MapWidget : public Widget, IMapCacheListener
	//=========================================================================
	{
		friend class MapWidgetPanTimerListener;

	public:
		MapWidget(int x, int y, int width, int height, Widget* parent);
		
		virtual ~MapWidget( );
		//
		// Map update scope
		//
		void enterMapUpdateScope( );
		void exitMapUpdateScope( bool immediate );
		void updateMap( );
		//
		// Map source property
		//
		MapSourceKind getMapSourceKind( ) const { return mSourceKind; }
		void setMapSourceKind( MapSourceKind sourceKind );
		//
		// Center position property
		//
		LonLat getCenterPosition( ) const;
		void setCenterPosition( LonLat position );
		PixelCoordinate getCenterPositionPixels( ) const;
		//
		// Magnification property
		//
		int getMagnification( ) const;
		void setMagnification( int magnification );
		//
		// Magnification scale display property
		//
		bool getHasScale( ) const { return mHasScale; }
		void setHasScale( bool hasScale ) { mHasScale = hasScale; }
		//
		// Smooth panning property
		//
		bool getHasSmoothPanning( ) const;
		void setHasSmoothPanning( bool hasSmoothPanning );
		//
		// Font property
		//
		Font* getFont( ) const { return mFont; }
		void setFont( Font* font ) { mFont = font; }

		//
		// Navigation
		//
		void scroll( MapWidgetScrollDirection direction, bool largeStep);
		//
		// Zooming
		//
		void zoomIn( );
		void zoomOut( );
		//
		// Widget overrides
		//
		virtual void setWidth( int width );
		virtual void setHeight( int height );
		//
		// Key handling
		//
		virtual bool handleKeyPress( int keyCode );
		virtual bool handleKeyRelease( int keyCode );
		//
		// IMapCacheListener implementation
		//
		virtual void tileReceived( MapCache* sender, MapTile* tile );
		//
		// Coord conversions
		//
		MAPoint2d worldPixelToWidget( PixelCoordinate wpx );
		PixelCoordinate widgetToWorldPixel( MAPoint2d pt );

	protected:
		//
		// Redraw
		//
		virtual void drawOverlay( );
		virtual void drawWidget( );
		Point getActualPosition( );

	private:
		void resetScreenImage( );
		void checkMapUpdateScope( );

		LonLat mCenterPositionLonLat;
		PixelCoordinate mCenterPositionPixels;
		LonLat mPanTargetPositionLonLat;
		PixelCoordinate mPanTargetPositionPixels;
		int mMagnification;
		MapSourceKind mSourceKind;
		int mMapUpdateNesting;
		PixelCoordinate mPrevCenter;
		int mPrevMagnification;
		MAHandle mScreenImage;
		bool mHasScale;
		MapWidgetPanTimerListener* mPanTimerListener;
		bool mHasSmoothPanning;
		Font* mFont;
		bool mTimerRunning;
	};
}
#endif // MAPWIDGET_H_