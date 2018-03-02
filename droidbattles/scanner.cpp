/***************************************************************************
                          scanner.cpp  -  description
                             -------------------
    begin                : Mon Apr 3 2000
    copyright            : (C) 2000 by Andreas Agorander
    email                : Bluefire@linux.nu
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "scanner.h"

scanner::scanner( screenobject &object, int arg1, int offset )
{
	ourlevel = arg1;
	ourbot = &object;
	width = 128;
	lastscandist = 65535;
	lastscanang = 2;
	maxscandist = ourlevel;
	scantimes = 0;
	scantimes2 = 0;
	relang = offset*4;
	scanshow = 0;
	threshold = 5;
	int count,count2;
	for( count=0;count<4;count++ )
	{
		for( count2=0;count2<4;count2++ )
		{
			stacktaken[count][count2]=false;
			portstack[count][count2]=0;
		}
	}
}

scanner::~scanner( )
{
}

	/**
		* This function needs cleanup and documentation!
		*/
void scanner::execute( )
{

  //Emit a scan pulse, search for closest visible object in
  //scan arc
  if( stacktaken[0][0] == true )
	{
		moveportstack( 0 );

		//Check angles and distance for every object that's a bot
		scanshow = 1;
		lastscandist = 65535;
		lastscanang = 2;
		int count;
		for( count=0;count<255;count++ )
		{
			if( (count != ourbot->getnum( )) &&
				(ourbot->iodevtobatt( 0,0,6,count,0 ) >= threshold) )
			{
				int ourX, ourY, hisX, hisY;
				int startang, endang, leftang, rightang, angle, mangle;
				int distX, distY, dist;

				ourX = ourbot->getXpos( );
				ourY = ourbot->getYpos( );
				hisX = ourbot->iodevtobatt( 0,0,1,count,0 );
				hisY = ourbot->iodevtobatt( 0,0,2,count,0 );

				mangle = ourbot->getdir( ) + relang;
				// when (relang != 0), mangle could contain an unnormalized angle
				if( mangle >= 1024 )
					mangle -= 1024;
				// that's it, now mangle is normalized (0..1023)
				startang = mangle - width;
				if( startang < 0 )
					startang += 1024;

				endang = mangle + width;
				if( endang >= 1024 )
					endang -= 1024;

				distX = ourX - hisX;
				distY = ourY - hisY;
        dist = int( sqrt( distX*distX + distY*distY ) );

				angle = int( atan2( distY , distX ) * 512 / pi );

				angle -= 512;
				if( angle >= 1024 )
					angle -= 1024;
				if( angle < 0 )
					angle += 1024;

				if( mangle > angle )
				{
					leftang = mangle - angle;
					rightang = angle + 1024 - mangle;
				}
				else
				{
					leftang = mangle + 1024 - angle;
					rightang = angle - mangle;
				}

				if( ( leftang < width || rightang < width ) && ( abs( dist )
								 < lastscandist ) && ( abs( dist ) < maxscandist ) )
				{
					lastscandist = dist;
          double widthinarc;
					if( leftang < width )
						widthinarc = width - leftang;
					else
						widthinarc = width + rightang;

					lastscanang = int( widthinarc/( ( width*2 ) /5 ) );
					lastscanid = count;
					lastscanfreq = ourbot->iodevtobatt( 0,0,8,count,0 );
					lastscandir = ourbot->iodevtobatt( 0,0,3,count,0 );
					lastscanspeed = ourbot->iodevtobatt( 0,0,4,count,0 );
					if( lastscanang == 5 )lastscanang--;

					int tdir,tbot,tint,tdist;  //The following lines so
					tdir = lastscanang - 2;    //that the scanned bot gets notified
					if( tdir < 0 )tdir = -tdir;
					tdist = int( double(lastscandist)/double(maxscandist) * 4 );
					tint = tdir + tdist;
					tdir = ((angle >> 7) << 7);
					tdir += 512;
					if( tdir >= 1024 )tdir -= 1024;
					tbot = count;
					ourbot->iodevtobatt( tbot,0,9,tint,tdir );

				}
			}
		}
	}
  //Set scan width
	if( stacktaken[1][0] == true )
	{
		width = portstack[1][0];
		moveportstack( 1 );
	}
  //Select return from inport 3
	if( stacktaken[2][0] == true )
	{
		wret = portstack[2][0];
		moveportstack( 2 );
	}
  //Set sensitivity
	if( stacktaken[3][0] == true )
	{
		threshold = portstack[3][0];
		moveportstack( 3 );
	}
}

	/**
		* Paint scanarc black
		*/
void scanner::erasegfx( QWidget *buffer )
{
	if( ispainted == true )
	{
		QPainter p( buffer );
		p.setPen( QColor( 0,0,0 ) );
		p.drawPie( (lastpaintX-maxscandist)>>6,(lastpaintY-maxscandist)>>6,
							 (maxscandist*2)>>6,(maxscandist*2)>>6,
								-(lastpaintang-lastpaintsize)*5.625,-lastpaintsize*11.25 );
		ispainted = false;
	}
}

	/**
		* Paint the white scanarc
		*/
void scanner::showgfx( QWidget *buffer )
{
	if( scanshow-- > 0 )
	{
		QPainter p( buffer );
		p.setPen( QColor( 255,255,255 ) );
		p.drawPie( (ourbot->getXpos( )-maxscandist)>>6,(ourbot->getYpos( )
								-maxscandist)>>6,(maxscandist*2)>>6,(maxscandist*2)>>6,
								-((ourbot->getdir( )+relang)-width)*5.625,-width*11.25 );
		lastpaintX = ourbot->getXpos( );
		lastpaintY = ourbot->getYpos( );
		lastpaintang = (ourbot->getdir( )+relang);
		lastpaintsize = width;
		ispainted = true;
	}
}

int scanner::getfromport( unsigned char port )
{
	switch ( port )
	{
		case 0 :
			return lastscandist;
		break;
		case 1 :
			return lastscanang;
		break;
		case 2 :
			return width;
		break;
		case 3 :
			if( wret == 0 )return lastscanfreq;
			if( wret == 1 )return lastscanid;
			if( wret == 2 )return lastscandir;
 			if( wret == 3 )return lastscanspeed;
		break;
	}
	return 0;
}
