/***************************************************************************
                          robots.cpp  -  description
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

#include "robots.h"

	/**
		* Init bot position, load program file and graphics
		*/
robots::robots( char *name,textmodeBattleArea &object,int mnum, confstruct config,
								int tm,bool er, bool ui )
{
	useUI = ui;
	int numdev = 0;
	int cost = 0;
	upcount = 0;
	team = tm;
	showerror = er;
	myfile = name;
	myfile = myfile.left( myfile.length( )-3 );
	myfile += "dat";

	ourarea = &object;

	Xpos = ourarea->getstartx( mnum );//Get start position from battlearea
	Ypos = ourarea->getstarty( mnum );
	direction = random( )%1024;

	fuelval = 0;
	mynum = mnum;
	myowner = mnum;
	maxx = ourarea->getareainfo( 0 );
	maxy = ourarea->getareainfo( 1 );
	armorval = 0;
	speed = 0;
	QFile f( name );        //Open the .bot file
	if( f.open( IO_ReadOnly ) )
	{
		QDataStream s( &f );
		unsigned int lng;
		char *tc;
		s.readBytes( tc,lng );
		unsigned char *my = (unsigned char *)&tc[0];
		showextragfx = true;
		f.close( );
		if( my[1] > config.maxram )         //Read in all devices
		{
			error( "Max amount of ram",name );
		}
		if( my[1] <= 9 )
		{
			cost += config.ramcost[my[1]];
			switch ( my[1] )
			{
				case 0 :
					ramdevice = new RAM( 1024,my );
				break;
				case 1 :
					ramdevice = new RAM( 2048,my );
				break;
				case 2 :
					ramdevice = new RAM( 4096,my );
				break;
				case 3 :
					ramdevice = new RAM( 8192,my );
				break;
				case 4 :
					ramdevice = new RAM( 16384,my );
				break;
				case 5 :
					ramdevice = new RAM( 24576,my );
				break;
				case 6 :
					ramdevice = new RAM( 32768,my );
				break;
				case 7 :
					ramdevice = new RAM( 49152,my );
				break;
				case 8 :
					ramdevice = new RAM( 65536,my );
				break;
			}
		}
		else
		{
			error( "File format error",name );
			ramdevice = new RAM( );
		}
		int x;

		for( x=0;x<32;x++ )
			hitabsorborder[x] = 0;
		int backx=31;
		int forx=0;
		int levelvalue = 0;
		for( x=0;x<32;x++ )
		{
			if( my[x*6+2] <= NUMDEV )
			{
				if( config.enabled[my[x*6+2]-1] == false && my[x*6+2] != 0 )
					error( "Using disabled device", name );
				if( my[x*6+3] <= 4 && my[x*6+2] > 0 )
				{
					numdev++;
					cost += config.cost[my[x*6+3]][my[x*6+2]-1];
					levelvalue = config.values[my[x*6+3]][my[x*6+2]-1];
				}
				if( my[x*6+3] > 4 )
				{
					error( "File format error",name );
					levelvalue = 0;
				}
			
				switch ( my[x*6+2] )
				{
					case 0 :
						devicelist[x] = new device( *this );
					break;
					case 1 :
						devicelist[x] = new robCPU( *ramdevice,*this,levelvalue,my[x*6+4],
																				my[x*6+5],my[x*6+6],my[x*6+7] );
					break;
					case 2 :
						devicelist[x] = new engine( *this, levelvalue );
					break;
					case 3 :
						devicelist[x] = new steering( *this, levelvalue );
					break;
					case 4 :
						devicelist[x] = new plasma( *this, levelvalue, my[x*6+4] );
					break;
					case 5 :
						devicelist[x] = new armor( *this, levelvalue );
						hitabsorborder[backx] = x;
						backx--;
					break;
					case 6 :
						devicelist[x] = new scanner( *this, levelvalue, my[x*6+4] );
					break;
					case 7 :
						devicelist[x] = new fuel( *this, levelvalue );
					break;
					case 8 :
						devicelist[x] = new chafflauncher( *this,levelvalue );
					break;
					case 9 :
						devicelist[x] = new turret( *this,levelvalue,my[x*6+4] );
					break;
					case 10 :
						devicelist[x] = new scandetect( *this );
					break;
					case 11 :
						devicelist[x] = new timedev( *this );
					break;
					case 12 :
						devicelist[x] = new shield( *this, levelvalue );
						hitabsorborder[forx] = x;
						forx++;
					break;
					case 13 :
						devicelist[x] = new repair( *this, levelvalue );
					break;
					case 14 :
						devicelist[x] = new communication( *this );
						ourradiodev = x;
					break;
					case 15 :
						devicelist[x] = new chiller( *this, levelvalue );
					break;
					case 16 :
						devicelist[x] = new cloaker( *this,levelvalue );
					break;
					case 17 :
						devicelist[x] = new minelayer( *this, levelvalue );
					break;
					case 18 :
						devicelist[x] = new radarmissilelauncher( *this, levelvalue,
																											ramdevice,my[x*6+4] );
					break;
					case 19 :
						devicelist[x] = new beamer( *this, levelvalue );
					break;
					case 20 :
						devicelist[x] = new rocketlauncher( *this, levelvalue,my[x*6+4] );
					break;
					default :
						devicelist[x] = new device( *this );
					break;
				}
			}
			else
			{
				error( "File format error",name );
				devicelist[x] = new device( *this );
			}
		}
		if( numdev > config.maxdev )
			error( "Max number of devices", name );
		if( cost > config.maxcost )
			error( "Max cost of bot",name );

		delete my;
	}
	else
	{
		error( "Couldn't open bot file!",name );
		ramdevice = new RAM;
		for( int x=0;x<32;x++ )
			devicelist[x] = new device( *this );
	}

	if( useUI )
	{
		erasegfx = new QPixmap;
		erasegfx->resize( 32,32 );
		erasegfx->fill( black );
		graphics = new QPixmap;
		graphics->resize( 32,32 );
		QString temp;
		temp = name;
		temp = temp.left( temp.length( )-3 );
		temp += "bmp";
		QFile f2( temp );
		if( f2.exists( ) == false )
		{
			temp = returninstalldir( );
			temp += "/pixmaps/skepp";
			temp += QString::number( mynum );
			temp += ".bmp";
		}
		if(graphics->load( temp ) == false )
		{
			graphics->fill( white );
		}
		else
			graphics->setMask( graphics->createHeuristicMask( ) );
		 //Set a mask that makes the bot background transparent
		piccols = graphics->width( )/32;
		picrows = graphics->height( )/32;
		currentrow = 0;
		rowchangeval = 0;
		degreesperpic = 1024/piccols;
	}
	size = 16;
	setheat( 0 );
}


robots::~robots( )
{
	int x;
	for( x=0;x<32;x++ )
		delete devicelist[x];
	ramdevice->removeowner( );
	if( ramdevice->getowners( ) == 0 )delete ramdevice;
	if( useUI )
	{
		delete graphics;
		delete erasegfx;
	}
}

	/**
		* Execute devices, adjust spedd and position
		*/
int robots::execute( )
{
	int x;
	currentradar = 5;
	for( x=0;x<32;x++ )             //Execute all devices
	{
		devicelist[x]->execute( );
	}
	double dir = getdir( ) * pi / 512;
	changepos( cos( dir ) * getspeed( ),sin( dir ) * getspeed( ) );//Update position
	rowchangeval += getspeed( );
	if( rowchangeval > 512 )
	{
		currentrow++;
		rowchangeval -= 512;
	}
	if( rowchangeval < 0 )
	{
		currentrow--;
		rowchangeval += 512;
	}
	if( currentrow < 0 )
		currentrow = picrows - 1;
	if( currentrow == picrows )
		currentrow = 0;

	upcount++;
	if( upcount > 10 )
	{
		upcount = 0;
		if( useUI )emit fuelchanged( fuelval,getheat( ) );
	}
	changeheat( -7 );

	if( getheat( ) > 500 && getheat( ) <= 600 )
	{
		objhit( 9,1 );
	}
	if( getheat( ) > 600 && getheat( ) <= 700 )
	{
		objhit( 9,2 );
	}
	if( getheat( ) > 700 && getheat( ) <= 800 )
	{
		objhit( 9,5 );
	}
	if( getheat( ) > 800 )
	{
		objhit( 9,999 );
	}

	return 0;
}

	/**
		* Paint bot black
		*/
void robots::eraseobject( QWidget *buffer )
{
	bitBlt( buffer,( oldX>>6 )-16,( oldY>>6 )-16,erasegfx );
	int x;
	if( gfxin == true )
	{
		for( x=0;x<32;x++ )
			devicelist[x]->erasegfx( buffer );
		gfxin = false;
	}
}

	/**
		* Show bot gfx on screen
		*/
void robots::showobject( QWidget *buffer, int opt )
{
	int degrees = getdir( )+(degreesperpic/2);
	if( degrees > 1023 )
		degrees -= 1024;

	int picpos = int( degrees / degreesperpic ) * 32;
	int ypicpos = currentrow * 32;
	
	int x;
	if( opt == 0 )
		bitBlt( buffer,( getXpos( )>>6 )-16,( getYpos( )>>6 )-16,graphics,picpos,
						ypicpos,32,32 );
	if( showextragfx == true )
	{
		for( x=0;x<32;x++ )
			devicelist[x]->showgfx( buffer );
		gfxin = true;
	}
}

	/**
		* Get values from device ports
		*/
int robots::getdevport( unsigned char port )
{
	int tempport = port%portsperdev;
	int tempdevice = int( port/portsperdev );
	int temp = devicelist[tempdevice]->getfromport( tempport );
	return temp;
}

	/**
		* Put values in device ports
		*/
void robots::putdevport( unsigned char port, unsigned short value )
{
	int tempport = port%portsperdev;
	int tempdevice = int( port/portsperdev );
	devicelist[tempdevice]->addinport( tempport,value );
}

	/**
		* Inbetween function for devices that wants to add screenobjects to battlearea
		*/
void robots::addscrobject( int X,int Y,int dir,int type, int arg1,
													 int arg2, void *arg3 )
{
	ourarea->addscrobject( mynum,X,Y,dir,type,arg1,arg2,arg3 );
}

int robots::returntype( )
{
	return 1;
}

	/**
		* Inbetween function for devices that want to communicate to battlearea
		*/
int robots::iodevtobatt( int bot,int dev,int choice,int arg1,int arg2 )
{
	return ourarea->devio( bot,dev,choice,arg1,arg2 );
}

	/**
		* Inbetween function for when one device wants to do something with
		* another device
		*/
int robots::iodevtodev( int dev,int action, int value )
{
	switch( action )
	{
		case 1 :
			if( dev < 32 && dev >= 0 )
				devicelist[dev]->setrelang( value );
		break;
		case 2 :
			return devicelist[dev]->returntype( );
		break;
		case 3 :
			return devicelist[dev]->returnspecial( );
		break;
		case 4 :
			devicelist[dev]->dospecial( value );
			emit armorchanged( armorval );
		break;
	}
	return 0;
}

int robots::getcollisiontype( )
{
	return 1;
}

int robots::getcollisionstrength( )
{
	return int(speed/5);
}

	/**
		* If hit, let armor and shield absorb hit.
		* If that doesn't help, die
		*/
int robots::objhit( int type,int strength )
{
	int x;
	int xy;
	int strengthleft = strength;

	int ifint;
	if( type == 9 )
	{
		ifint = 1;
	}
	else
	{
		ifint = 0;
	}
	for( x=0;x<32;x++ )
	{
		xy = hitabsorborder[x];
		strengthleft = devicelist[xy]->absorbhit( strengthleft,ifint );
		if( strengthleft <= 0 )
			break;
	}
	if( useUI )emit armorchanged( armorval );

	if( strengthleft > 0 )
		return objhitdestroyed;
	else
		return 0;
}

int robots::getsize( )
{
	return size;
}

const char* robots::getdebug1( )
{
	return debug1;
}

const char* robots::getdebug2( )
{
	return debug2;
}

void robots::setdebug1( int msg )
{
	QTextStream ts( debug1, IO_ReadWrite );
	ts << "Angle is: " << msg << "  ";
}

void robots::setdebug2( int msg )
{
	QTextStream ts( debug2, IO_ReadWrite );
	ts << "distance is: " << msg << "  ";
}

	/**
		* Show error message (mainly for showing that bot doesn't conform to .cfg file)
		*/
void robots::error( char *string, char *name )
{
	if( showerror && useUI )
	{
		QString msg = "The bot ";
		msg += name;
		msg += "\nbreaks the following rule in the config file: \n";
		msg += string;
		msg += team;	
		QMessageBox::information( 0,"Message from the bot",msg );
		return;
	}
}

void robots::receiveradio( int sig )
{
	devicelist[ourradiodev]->dospecial( sig,0 );
}

int robots::getmem( )
{
	return ramdevice->returnsize( );
}

	/**
		* Add interrupt to one of bots CPU:s
		*/
void robots::addinterrupt( int inter )
{
	if( inter > 255 )
		return;
	int x;
	for( x=0;x<32;x++ )
	{
		if( devicelist[x]->returntype( ) == CPUtype )
		{
			if( devicelist[x]->returnspecial( ) == CPUwithint )
			{
				devicelist[x]->addinport( 0,inter );
				break;
			}
		}		
	}
}

	/**
		* Returns debugstructure from first CPU
		*/
struct debugcontents robots::returndbgcont( )
{
	int x;
	for( x=0;x<32;x++ )
	{
		if( devicelist[x]->returntype( ) == 9 )
		{
			return devicelist[x]->returndbg( );
			break;
		}		
	}
}

/**
 * Returns number of CPUs
 */
int robots::numCPUs()
{
  int num = 0;
  for (int x = 0; x <32; x++)
    if (devicelist[x] && (devicelist[x]->returntype() == 9)) num++;
  return num;
}

/**
 * Returns debugstructure from all CPUs
 */

std::list<struct debugcontents>* robots::returndbgcont2( )
{
  std::list<debugcontents> *dc = new std::list<debugcontents>;
	for(int x=0;x<32;x++ )
		if( devicelist[x] && (devicelist[x]->returntype() == 9))
			dc->push_back(devicelist[x]->returndbg( ));
  return dc;
}
	/**
		* Object is seen by radar...
		*/
int robots::returnradar( )
{
	return currentradar;
}

	/**
		* When object is scanned, check if we have a scandetector...
		*/
void robots::objscanned( int intensity,int dir )
{
	int x;
	for( x=0;x<32;x++ )
	{
		if( devicelist[x]->returntype( ) == 11 )
		{
			devicelist[x]->dospecial( intensity,dir );
			break;
		}		
	}
}

void robots::setradar( int x )
{
	currentradar = x;
}

	/**
		* When dumpRAM button in debugwindow is pressed
		* this function opens a file and dumps RAM
		* contents to it
		*/
void robots::dumpRAM( )
{
	for( int x=0;x<256;x++ )
	{
		QString fname = "BBdump";
		fname += QString::number( x );
		fname += ".bin";
		QFile f( fname );
		if( !f.exists( ) )
		{
			if( f.open( IO_WriteOnly ) )
			{
				for( int y=0;y<ramdevice->returnsize( );y++ )
				{
					f.putch( ramdevice->getbyte( y ) );
				}
				f.close( );
			}
			break;
		}
	}
}