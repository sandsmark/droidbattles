/***************************************************************************
                          battlearea.cpp  -  description
                             -------------------
    begin                : Sun Apr 2 2000
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

#include "battlearea.h"
//Added by qt3to4:
#include <Q3TextStream>
#include <QLabel>
#include <QResizeEvent>
#include <QCloseEvent>
bool SingleStepMode = false;

	/**
		* Constructor, inits area and starts first battle round
		*/
battlearea::battlearea( char *nam1,char *nam2,char *nam3,char *nam4,
												char *nam5,char *nam6,char *nam7,char *nam8,int numf,
												int mx, int xs, int ys, bool ifteams, int *bteams,
												bool tourney,bool fast,int mode,int maxp,
												bool ifdebug,Q3MultiLineEdit *dbedit,
												int *dbl, int *dbm )
{

	debugenabled = ifdebug;
	iffast = fast;
	battlemode = mode;
	maxpoints = maxp;

	hideresmsg = tourney;

	isteams = ifteams;
	xsize = xs;
	ysize = ys;
	ifdelete = false;

	// OPen the current config file
	maxrounds = mx;
	QString tempname = QDir::homeDirPath( );
	tempname += "/droidbattles/current.cfg";
	QFile f( tempname );
	if( !f.open( QIODevice::ReadOnly ) )
	{
		//TODO: add error message
		delete this;
		return;
	}

	Q3TextStream s( &f );
	int x,y;
	for(x=0;x<maxbots;x++)
	{
		botteams[x] = bteams[x];
	}
	QString dummy;
	int i;
//	bool ch;
	s >> dummy;
	s >> i;
	config.maxdev = i;
	s >> dummy;
	s >> i;
	config.maxcost = i;
	s >> dummy;
	s >> i;
	config.maxram = i;
	s >> dummy;
	for( x=0;x<9;x++ )
	{
		s >> i;
		config.ramcost[x] = i;
	}
	for( x=0;x<NUMDEV;x++ )
	{
		s >> dummy;
		s >> i;
		if( i == 1 )
			config.enabled[x] = true;
		else
			config.enabled[x] = false;
		for( y=0;y<5;y++ )
		{
			s >> i;
			config.cost[y][x] = i;	
			s >> i;
			config.values[y][x] = i;	
		}
	}		
	
	//Initialize vars
	numfights = numf;
	fightsfought = 0;
	names[0] = nam1;
	names[1] = nam2;
	names[2] = nam3;
	names[3] = nam4;
	names[4] = nam5;
	names[5] = nam6;
	names[6] = nam7;
	names[7] = nam8;
	for( x=0;x<8;x++ )
		fightswon[x] = 0;

	scrolling = new Q3ScrollView( this,0,Qt::WPaintClever );
	scrolling->setGeometry( 16,16,524,524 );
	mydrw = new QWidget( );
	infowindow = new QWidget( );
	infowindow->resize( 550,420 );

	debug1 = new QLabel( "a", infowindow );
//	debug1->setGeometry( 0,0,150,20 );
	debug2 = new QLabel( "b", infowindow );
//	debug2->setGeometry( 0,25,150,20 );

	debug1->hide( );
	debug2->hide( );
	scrolling->addChild( mydrw );
	mydrw->setGeometry( 0,0,xsize>>6,ysize>>6 );
	mydrw->show( );
	mydrw->setBackgroundMode( Qt::PaletteBase );
	mydrw->setPalette( QPalette( QColor( 0,0,0 ) ) );
	playb = new PixButton( "Play",1,this );
	pauseb = new PixButton( "Pause",1,this );
	singles = new PixButton( "Singlestep",1,this );
	playb->setGeometry( 540,20,70,20 );
	pauseb->setGeometry( 540,40,70,20 );
	singles->setGeometry( 540,60,70,20 );
	QObject::connect( playb,SIGNAL( clicked( ) ),this,SLOT( play( ) ) );
	QObject::connect( pauseb,SIGNAL( clicked( ) ),this,SLOT( pause( ) ) );
	QObject::connect( singles,SIGNAL( clicked( ) ),this,SLOT( singlestep( ) ) );

	eventH = new QTimer( );
	QObject::connect( eventH, SIGNAL( timeout( ) ),
										this, SLOT( execute( ) ) );
	if( ifdebug )
	{
    // keep parameters
    _dbedit = dbedit;
    _dbl    = dbl;
    _dbm    = dbm;

//		dbgwindow = new debugwindow( dbedit,&dbl[0],&dbm[0] );
//		dbgwindow->resize( 300,405 );
//		dbgwindow->show( );
//		QObject::connect( dbgwindow,SIGNAL( dumpmem( ) ),this,SLOT( dmem( ) ) );
	}
  missilesLaunched = 0;

	setMinimumSize( 150,150 );
	resize( 640,570 );
	startonebattle( firstrun );

	setBackgroundPixmap( Pixmapholder::getpm( 3 ) );

}

void battlearea::resizeEvent( QResizeEvent *e )
{
	scrolling->setGeometry( 16,16,width( )-116,height( )-46 );
	playb->setGeometry( width( )-100,20,70,40 );
	pauseb->setGeometry( width( )-100,60,70,40 );
	singles->setGeometry( width( )-100,100,70,40 );
}

	/**
		* Starts the timer that calls execute (executed by "play" button)
		*/
void battlearea::play( )
{
	if( iffast == true )
		eventH->start( 0 ); //As fast as possible
	else
		eventH->start( 20 );//20 ms between ticks (50 times/second)
	runmode = 1;
}

	/**
		* Stops the timer that calls execute (executed by "pause" button)
		*/
void battlearea::pause( )
{
	eventH->stop( );
	runmode = 0;
}

	/**
		* Runs a single battle tick
		*/
void battlearea::singlestep( )
{
	if( debugenabled )SingleStepMode = true;	
	this->execute( );
	if( debugenabled )SingleStepMode = false;
}

	/**
		* Destructor, deletes self
		*/
battlearea::~battlearea( )
{
	eventH->stop( );
	delete eventH;
	delete infowindow;
	std::list<debugwindow*>::iterator i;
	for (i=dbgwindows.begin(); i!=dbgwindows.end(); i++)
    delete *i;
  dbgwindows.clear();
//	if( debugenabled )delete dbgwindow;
	int x;
//	for( x=0;x<maxobjects;x++ )
//		delete objects[x];
}

	/**
		* start one round of fight
		* In case this isn't the first round, deallocate previous mem
		*/
void battlearea::startonebattle( int y )
{
	int x;
	//If this isn't the first run, deallocate the memory
	//from the run before this
	if( y == notfirstround )
	{
		//Deallocate memory
		for( x=0;x<maxbots;x++ )
			delete binfo[x];
		for( x=0;x<maxobjects;x++ )
			delete objects[x];
	}

	//Randomize start positions and make sure the bots don't start to
	//close to each other
	xstarts[0] = random( )%xsize;
	ystarts[0] = random( )%ysize;
	for( x =1;x<maxbots;x++ )
	{
		int dst=minstartdistance-1;
		int tries=0;
		while( dst < minstartdistance && tries < 128 )
		{
			dst = minstartdistance;
			xstarts[x] = random( )%xsize;
			ystarts[x] = random( )%ysize;
			for( y=0;y<x;y++ )
			{
				int xdiff = abs(xstarts[y] - xstarts[x]);
				int ydiff = abs(ystarts[y] - ystarts[x]);
				int tdist = int( sqrt((xdiff*xdiff)+(ydiff*ydiff)) );
				if( tdist < dst )dst = tdist;
			}
			tries++;
		}
	}

	//Load the bots
	QString tn;
	for( x=0;x<maxbots;x++ )
	{
		tn = names[x];
		if( !tn.isEmpty( ) )
			objects[x] = new robots( (char*)tn.data( ),*this,x,config,botteams[x] );
		else
			objects[x] = new screenobject( );

	 	binfo[x] = new botinfo( names[x],objects[x],objects[x]->armorval,
														infowindow );
  }

  if (debugenabled) {
    std::list<debugwindow*>::iterator i;
    for (i=dbgwindows.begin(); i!=dbgwindows.end();i++)
      delete *i;
    dbgwindows.clear();
    // the bot to be debugged is objects[debugbot]
    assert(objects[debugbot] != NULL);
    assert(objects[debugbot]->returntype() == 1);
    int nCpus = ((robots*)objects[debugbot])->numCPUs();
    for( int x=0;x<nCpus;x++ ) {
      debugwindow* dw = new debugwindow( _dbedit,&_dbl[0],&_dbm[0] );
      dw->resize( 300,405 );
      dw->show( );
      QString title;
      title.sprintf("CPU #%d",x);
      dw->setCaption(title);  // set title
      dbgwindows.push_back(dw);
    }
  }

	//Make all other positions as "standard" screenobjects
	for( x=maxbots;x<maxobjects;x++ )
		objects[x] = new screenobject( );

	//Create the infoboxes for the bots
	for( x=0;x<maxbots;x++ )
	{
		binfo[x]->setGeometry( 10,10+x*50,540,50 );
		QObject::connect( objects[x],SIGNAL( armorchanged( int ) ),binfo[x],
											SLOT( armorupdated( int ) ) );
		QObject::connect( binfo[x], SIGNAL( changeinset( bool ) ), objects[x],
											SLOT( setextragfx( bool ) ) );
		QObject::connect( objects[x],SIGNAL( fuelchanged( int,int ) ),binfo[x],
											SLOT( updatefuel( int,int ) ) );
		QObject::connect( objects[x],SIGNAL( messagechanged( char * ) ),binfo[x],
											SLOT( newmessage( char * ) ) );
	}
	roundsrun = 0;
	infowindow->show( );
	mydrw->repaint( );
	if( iffast == true )
	{
		eventH->start( 0 );
		runmode = 1;
	}
	else
	{
		if( !debugenabled )
		{
			eventH->start( 20 );
			runmode = 1;
		}
	}
}

	/**
		* Executed ~50 times a second (normally)
		* each time one "step" is executed in the battle
		*/

void battlearea::execute( )
{
//	eventH->stop( );
	int x;
	roundsrun++;
	if( roundsrun > maxrounds )        //If the times up...
	{
		if( battlemode == 1 || battlemode == 0 )
		{
			for( x=0;x<maxbots;x++ )
			{
		  	objects[x]->eraseobject( mydrw );//Erase all bots (to call a draw)
		  	delete objects[x];
				objects[x] = new screenobject( );
			}
		}
		if( battlemode == 2 )
		{
			checkwin = true;
			maxpoints = 0;
		}
	}
	for( x=0;x<maxobjects;x++ )               //Remove the gfx from last round
		objects[x]->eraseobject( mydrw );

	for( x=0;x<maxobjects;x++ )
	{
		int ifdel = objects[x]->execute( ); //Let each object execute,
																				//move around and things like that
		objects[x]->showobject( mydrw );    //Let each object paint itself
		int x2;
		if( objects[x]->returntype( ) > 0 )//Check If the object exists and
		{                                  //is a "collidable" object
			for( x2=(x+1);x2<maxobjects;x2++ )	//Loop through all possible objects
			{																	//(to check for collisions)

				// Also, if the objects has the same collid (and it's != 256)
				// (Eg, bullets fired by the same bot)  don't issue a collision
				if( objects[x2]->returntype( ) > 0 &&
					( (objects[x]->getcollid( ) == collenabled ||
						objects[x2]->getcollid( ) == collenabled) ||
					(	objects[x]->getcollid( ) != objects[x2]->getcollid( ) ) ) )
				{                              //If object exists
					int xx1,xx2,yy1,yy2,dist,dx,dy;

					xx1 = objects[x]->getXpos( );          //
					xx2 = objects[x2]->getXpos( );         // Get positions
					dx = (xx1 - xx2)/2;                        // and distances
					yy1 = objects[x]->getYpos( );          // between each object
					yy2 = objects[x2]->getYpos( );         //
					dy = (yy1 - yy2)/2;                        //
					dist = int( sqrt( (dx*dx) + (dy*dy) ) );   //
					dist *= 2;

					if( dist < (( objects[x]->getsize( )<<6)+(objects[x2]->getsize( )<<6 )) )
					{   //If they're bigger than their distance they have collided
						int xxx;
						for ( xxx=254;xxx > 128;xxx-- )
						{
							if( objects[xxx]->returntype( ) == 0 )
							{
								delete objects[xxx];
								objects[xxx] = new explosion( (xx1+xx2)/2,(yy1+yy2)/2,*this );
								break;
							}
						}
						int type1,type2,str1,str2;
						type1 = objects[x]->getcollisiontype( );
						type2 = objects[x2]->getcollisiontype( );
						str1 = objects[x]->getcollisionstrength( );// Get the damage they will
						str2 = objects[x2]->getcollisionstrength( );// inflict on each other
						if( type1 == 1 )    // If he collided with a bot
						{
							objects[x2]->setspeed( -(objects[x2]->getspeed( )/2) );
							double dir = objects[x2]->getdir( ) * toradians; //Change dir
							objects[x2]->changepos( cos( dir ) * objects[x2]->getspeed( ),
																			sin( dir ) * objects[x2]->getspeed( ) );
						}
						if( type2 == 1 )
						{
							objects[x]->setspeed( -(objects[x]->getspeed( )/2) );
							double dir = objects[x]->getdir( ) * toradians;
							objects[x]->changepos( cos( dir ) * objects[x]->getspeed( ),
																		 sin( dir ) * objects[x]->getspeed( ) );
						}
						xx1 = objects[x]->getXpos( );          //
						xx2 = objects[x2]->getXpos( );         // Get positions
						dx = xx1 - xx2;                        // and distances between
						yy1 = objects[x]->getYpos( );          // each object
						yy2 = objects[x2]->getYpos( );         //
						dy = yy1 - yy2;                        //
						dist = int( sqrt( dx*dx + dy*dy ) );   //

						if( dist < ((objects[x]->getsize()<<6)+(objects[x2]->getsize( )<<6))
								&& objects[x]->returntype( ) ==1 && objects[x2]->returntype( )
							 ==1 )  //If they're bigger than their distance, move them apart
						{
							double angl = atan2( dy,dx );
							int dst = (objects[x]->getsize( )<<6)+
												(objects[x2]->getsize( )<<6)-dist;
							objects[x]->changepos( cos( angl )*((dst+16)/2),sin( angl )*
												((dst+16)/2) );
							objects[x2]->changepos( cos( angl+pi )*((dst+16)/2),
												sin( angl+pi )*((dst+16)/2) );
						}
						int x2owner = objects[x2]->getowner( );
						if( objects[x2]->objhit( 9,str1 ) == 1 )
						{
							switch( battlemode )
							{
								case 0 :
									objects[x2]->eraseobject( mydrw );
									delete objects[x2];
									objects[x2] = new screenobject( );
								break;
								case 1 :
									objects[x2]->eraseobject( mydrw );
									if( x < 8 && objects[x2]->returntype( ) == 1 )
									{
										fightswon[x2]++;
										delete objects[x2];
										if( fightswon[x2] < maxpoints )
										{
											//Calc X and Y position
											xstarts[x2] = random( )%xsize;
											ystarts[x2] = random( )%ysize;
											objects[x2] = new robots( (char *)names[x2].data( ),
																		*this,x2,config,botteams[x2],false );
											QObject::connect( objects[x2],
												SIGNAL( armorchanged( int ) ),binfo[x2],
												SLOT( armorupdated( int ) ) );
											QObject::connect( binfo[x2],
												SIGNAL( changeinset( bool ) ), objects[x2],
												SLOT( setextragfx( bool ) ) );
											QObject::connect( objects[x2],
												SIGNAL( fuelchanged( int,int ) ),binfo[x2],
												SLOT( updatefuel( int,int ) ) );
											QObject::connect( objects[x2],
												SIGNAL( messagechanged( char * ) ),binfo[x2],
												SLOT( newmessage( char * ) ) );
											objects[x2]->objhit( 0,0 );
										}
										else
										{
											objects[x2] = new screenobject( );
											fightswon[x2] = roundsrun;
										}
									}
									else
									{
										delete objects[x2];
										objects[x2] = new screenobject( );
									}
								break;
								case 2 :  //If it's a deathmatch battle
									objects[x2]->eraseobject( mydrw );
									if( objects[x2]->returntype( ) == 1 )
									{
										if( objects[x]->getowner( ) < 8 &&
												x2 != objects[x]->getowner( ) )
											fightswon[objects[x]->getowner( )]++;
										checkwin = true;
										//Calc X and Y position
										xstarts[x2] = random( )%xsize;
										ystarts[x2] = random( )%ysize;
										objects[x2] = new robots( (char *)names[x2].data( ),*this,
											x2,config,botteams[x2],false );
										QObject::connect( objects[x2],
											SIGNAL( armorchanged( int ) ),binfo[x2],
											SLOT( armorupdated( int ) ) );
										QObject::connect( binfo[x2],
											SIGNAL( changeinset( bool ) ), objects[x2],
											SLOT( setextragfx( bool ) ) );
										QObject::connect( objects[x2],
											SIGNAL( fuelchanged( int,int ) ),binfo[x2],
											SLOT( updatefuel( int,int ) ) );
										QObject::connect( objects[x2],
											SIGNAL( messagechanged( char * ) ),binfo[x2],
											SLOT( newmessage( char * ) ) );
										objects[x2]->objhit( 0,0 );
									}
									else
									{
										delete objects[x2];
										objects[x2] = new screenobject( );
									}
								break;
							}
						}
						if( objects[x]->objhit( 9,str2 ) == 1 )//If the damage killed him
						{
							switch( battlemode )
							{
								case 0 :  //If it's a normal battle
									objects[x]->eraseobject( mydrw );      //Erase him
									delete objects[x];
									objects[x] = new screenobject( );
									x2 = maxobjects;
									continue;
								break;
								case 1 :  //If it's a survival battle
									objects[x]->eraseobject( mydrw );
									if( x < 8 && objects[x]->returntype( ) == 1 )
									{
										fightswon[x]++;
										delete objects[x];
										x2 = maxobjects;
										if( fightswon[x] < maxpoints )
										{
											//Calc X and Y position
											xstarts[x] = random( )%xsize;
											ystarts[x] = random( )%ysize;
											objects[x] = new robots( (char *)names[x].data( ),*this,
												x,config,botteams[x],false );
											QObject::connect( objects[x],
												SIGNAL( armorchanged( int ) ),binfo[x],
												SLOT( armorupdated( int ) ) );
											QObject::connect( binfo[x],
												SIGNAL( changeinset( bool ) ), objects[x],
												SLOT( setextragfx( bool ) ) );
											QObject::connect( objects[x],
												SIGNAL( fuelchanged( int,int ) ),binfo[x],
												SLOT( updatefuel( int,int ) ) );
											QObject::connect( objects[x],
												SIGNAL( messagechanged( char * ) ),binfo[x],
												SLOT( newmessage( char * ) ) );
											objects[x]->objhit( 0,0 );
										}
										else
										{
											objects[x] = new screenobject( );
											fightswon[x] = roundsrun;
										}
									}
									else
									{
										delete objects[x];
										objects[x] = new screenobject( );
										x2 = maxobjects;
										continue;
									}
								break;
								case 2 :  //If it's a deathmatch battle
									objects[x]->eraseobject( mydrw );
									if( objects[x]->returntype( ) == 1 )
									{
										if( x2owner < 8 && x != x2owner )
											fightswon[x2owner]++;
										delete objects[x];
										x2 = maxobjects;
										checkwin = true;
										//Calc X and Y position
										xstarts[x] = random( )%xsize;
										ystarts[x] = random( )%ysize;
										objects[x] = new robots( (char *)names[x].data( ),*this,x,
											config,botteams[x],false );
										QObject::connect( objects[x],
											SIGNAL( armorchanged( int ) ),binfo[x],
											SLOT( armorupdated( int ) ) );
										QObject::connect( binfo[x],
											SIGNAL( changeinset( bool ) ), objects[x],
											SLOT( setextragfx( bool ) ) );
										QObject::connect( objects[x],
											SIGNAL( fuelchanged( int,int ) ),binfo[x],
											SLOT( updatefuel( int,int ) ) );
										QObject::connect( objects[x],
											SIGNAL( messagechanged( char * ) ),binfo[x],
											SLOT( newmessage( char * ) ) );
										objects[x]->objhit( 0,0 );
									}
									else
									{
										delete objects[x];
										objects[x] = new screenobject( );
										x2 = maxobjects;
										continue;
									}
								break;
							}
						}
					}
  			}
			}
		}
		if( ifdel == -1 )            //If the object ordered it's own destruction
		{                            //Example: shot that gets outside of screen
			objects[x]->eraseobject( mydrw );
			delete objects[x];
			objects[x] = new screenobject( );
		}
	}

	//Here, check if the battle has ended (eg. <= 1 bot or <= 1 team is left)

	int numofbots = 0;
	char botnum;
	if( isteams )    //If teams
	{
		alive[0] = 0;
		alive[1] = 0;
		alive[2] = 0;
		alive[3] = 0;
		for( x=0;x<maxbots;x++ )   //Mark teams with bots left
		{
			if( objects[x]->returntype( ) == doesexist )
			{
				int yy;
				yy = objects[x]->getteam( );
				if(yy > 3 || yy < 0)yy=0;
				alive[yy] = 1;
			}
		}
		for( x=0;x<4;x++ )     //Count them
		{
			if( alive[x] == 1 )
			{
				numofbots++;
				botnum = x;
			}
		}
		if( numofbots <= 1 )  //If battle is over
		{
			eventH->stop( );
			if( numofbots == 1 )
				fightswon[botnum]++;
			fightsfought++;
			if( fightsfought >= numfights ) //If all rounds of battle is over
			{
				int winbot=0;
				int curval=0;
				bool draw=false;
				for( x=0;x<maxteams;x++ )
				{
					if( fightswon[x] == curval )
						draw = true;
					if( fightswon[x] > curval )
					{
						curval = fightswon[x];
						winbot = x;
						draw = false;
					}
				}
				QString msg;
//				ermsg = new QMessageBox( );
//				ermsg->setCaption( "Fight ended" );
				if( draw == false )
				{
					msg = " Team ";
					msg += int(winbot)+'1';
					msg += " won!";
				}
				else
					msg = "Fight was a draw";
//				ermsg->setText( msg );
//				ermsg->setButtonText( 0, "OK" );
//				int ret = ermsg->exec( );
//				delete ermsg;
				QMessageBox::information( 0, "Fight Ended",msg );
				ifdelete = true;
			}
			else
				startonebattle( notfirstround ); //If we have rounds left, continue
		}                                    // with a new round
	}

	if( !isteams && (battlemode == 0 || battlemode == 1) )
	{
		for( x=0;x<maxbots;x++ )
		{
			if( objects[x]->returntype( ) == doesexist )
			{
				numofbots++;                       //Count the number of bots alive
				botnum = x;
			}
		}
		if( numofbots <= 1 )         //If the current fight has ended
		{
			eventH->stop( );           //Stop doing rounds of fight
			if( numofbots == 1 )       //If we have a winner ,count up his points
				fightswon[botnum]++;
			fightsfought++;
			if( fightsfought >= numfights )  //If we have done all the rounds of
			{                // fights we should have, Determine the overall winner
				int winbot=0;
				int curval=0;
				int curval2=1000;
				bool draw=false;
				for( x=0;x<maxbots;x++ )
				{
					if( fightswon[x] == curval )
						draw = true;
					if( fightswon[x] > curval )
					{
						curval = fightswon[x];
						winbot = x;
						draw = false;
					}
					if( fightswon[x] < curval2 && names[x] != "" )
					{
						curval2 = fightswon[x];
						botnum = x;
					}
				}
				QString msg;
				if( !hideresmsg )
				{
					switch ( battlemode )
					{
						case 0 :
					 	for( int xx = 0;xx<8;xx++ )
					 	{
							if( names[xx] != "" )
							{
								msg += " Bot ";
								msg += names[xx];
								msg += " won ";
								msg += QString::number( fightswon[xx] );
								msg += " fights.\n";
							}
						}
						break;
						case 1 :
							msg += " Bot ";
							msg += names[botnum];
							msg += " won with ";
							msg += QString::number( maxpoints-fightswon[botnum] );
							msg += " lives left!\n";
						 	for( int xx = 0;xx<8;xx++ )
						 	{
								if( names[xx] != "" && xx != botnum )
								{
									msg += " Bot ";
									msg += names[xx];
									msg += " survived ";
									msg += QString::number( fightswon[xx] );
									msg += " cycles.\n";
								}
							}
						break;
					}
					QMessageBox::information( 0,"Fight ended",msg );
				}
				else
					emit battledone( fightswon[0], fightswon[1] );

				ifdelete = true;
			}
			else
				startonebattle( notfirstround ); //If we have fights left,start a new
		}
	}

	if( battlemode == 2 && checkwin )
	{
		checkwin = false;
		for( x=0;x<8;x++ )
		{
			if( fightswon[x] >= maxpoints )
			{
				eventH->stop( );
//				ermsg = new QMessageBox( );
//				ermsg->setCaption( "Fight ended" ); //Show the win message
				QString msg;
			 	for( int xx = 0;xx<8;xx++ )
			 	{
					if( names[xx] != "" )
					{
						msg += " Bot ";
						msg += names[xx];
						msg += " got ";
						msg += QString::number( fightswon[xx] );
						msg += " frags.\n";
					}
				}
//				ermsg->setText( msg );
//				ermsg->setButtonText( 0, "OK" );
//				int ret = ermsg->exec( );
//				delete ermsg;
				QMessageBox::information( 0,"Fight ended",msg );
				ifdelete = true;
				break;
			}
		}
	}


	if( debugenabled )  //If this is a "quick battle", update register content info and such
    if (objects[debugbot]->returntype() == 1) // for robots only
    {
      std::list<struct debugcontents> *dc = ((robots*)objects[debugbot])->returndbgcont2();
      assert(dc->size() == dbgwindows.size());
      std::list<debugwindow*>::iterator i = dbgwindows.begin();
      std::list<debugcontents>::iterator j = dc->begin();
      for (;i!=dbgwindows.end();i++,j++)
        (*i)->updatedata(*j);
      delete dc;
    }
//		dbgwindow->updatedata( objects[debugbot]->returndbgcont( ) );

/*	if( runmode == 1 )
	{
		if( iffast )
			eventH->start( 0 );
		else
			eventH->start( 20 );
	}*/

	if( ifdelete == true )
		delete this;
}

	/**
		* If user presses the X in the bar...
		*/
void battlearea::closeEvent( QCloseEvent *e )
{
	delete this;
}

	/**
		* If a device wants to add a screenobject (as a shot) he calls
		* this function (via his bot)
		*/
void battlearea::addscrobject( int owner,int X,int Y,int dir,int type,
															 int arg1,int arg2, void *arg3 )
{
	int x;
	for( x=0;x<maxobjects;x++ )
	{
		if( objects[x]->returntype( ) == doesnotexist )
		{
			delete objects[x];
			RAM *temp3 = (RAM *)arg3;
			switch ( type )
			{
				case 0 :
					objects[x] = new screenobject( );
				break;
				case 1 :
//					objects[x] = new robots( "unnamed.bot",*this,x );
				break;
				case 2 :
					objects[x] = new missile( X,Y,dir,arg1,x,*this );
				break;
				case 3 :
					objects[x] = new mine( X,Y,*this,owner );
				break;
				case 4 :
					objects[x]=new radarmissile(X,Y,dir,arg1,arg2,x,*this,temp3,owner);
          ++missilesLaunched;
          if (debugenabled && (owner==debugbot))
            ((radarmissile*)objects[x])->createDbgWindow(missilesLaunched,
                _dbedit, _dbl, _dbm);
				break;
				case 5 :
					objects[x] = new beam( X,Y,dir,arg1,*this,owner );
				break;
				case 6 :
					objects[x] = new rocket( X,Y,dir,arg1,x,*this,owner );
				break;
				case 7 :
					objects[x] = new chaff( X,Y,dir,arg1,*this );
				break;
				default:
					objects[x] = new screenobject( );
			}
			break;
		}
	}
}

	/**
		* If a device (as the scanner) needs info about
		* the other screenobjects it calls this function
		* (via his bot)
		*/
/*int battlearea::devio( int bot,int dev,int choice,int arg1,int arg2 )
{
	switch ( choice )
	{
		case 1 :     //getXpos
			return objects[arg1]->getXpos( );
		break;
		case 2 :     //getYpos
			return objects[arg1]->getYpos( );
		break;
		case 3 :     //getdir
			return objects[arg1]->getdir( );
		break;
		case 4 :     //getspeed
			return objects[arg1]->getspeed( );
		break;
		case 5 :     //delete screenobject
			delete objects[bot];
			objects[bot] = new screenobject( );
		break;
		case 6 :
			return objects[arg1]->returnradar( );
		break;
		case 7 :
			int x;
			for( x=0;x<maxbots;x++ )
			{
				if( objects[x]->returntype( ) == doesexist && objects[x]->getteam( )
						== bot && ( arg2 == 255 || objects[x]->getnum( ) == arg2 ))
					objects[x]->receiveradio( arg1 );
			}
		break;
		case 8 :
			return objects[arg1]->getteam( );
		break;
		case 9 :
			objects[bot]->objscanned( arg1,arg2 );
		break;
		case 10 :
			return getareainfo( 0 );
		break;
		case 11 :
			return getareainfo( 1 );
		break;
		case 12 :
			return getareainfo( 2 );
		break;

	}
	return 0;
} */

	/**
		* Returns info about the battlearea
		*/
/*int battlearea::getareainfo( int choice )
{
	switch ( choice )
	{
		case 0 :
			return xsize;
		break;
		case 1 :
			return ysize;
		break;
		case 2 :
			return battlemode;
		break;
	}
	return 0;
} */


	/**
		* This function issues special areal (noncollision) hits.
		* The AS-rocket uses it
		*/
void battlearea::explosions( int x,int y,int rad,int strength,int whichobject)
{
	int X1,Y1,D1,S1,z;
	for( z=0;z<maxbots;z++ )
	{
		if( z == whichobject )continue;
		if( !objects[z]->areaexplosionaffects( ) )continue;
		X1 = objects[z]->getXpos( );
		Y1 = objects[z]->getYpos( );
		D1 = int( sqrt( ((X1-x)*(X1-x))+((Y1-y)*(Y1-y)) ) );
		if( D1 >= rad )continue;
		S1 = strength-( D1*strength/rad );
		if( objects[z]->objhit( 9,S1 ) == 1 )  //If the damage killed him
		{
		  objects[z]->eraseobject( mydrw );      //Erase him
			switch ( battlemode )
			{
				case 0 :
				  delete objects[z];
					objects[z] = new screenobject( );
				break;
				case 1 :
					if( z < 8 && objects[z]->returntype( ) == 1 )
					{
						fightswon[z]++;
						delete objects[z];
						if( fightswon[z] < maxpoints )
						{
							//Calc X and Y position
							xstarts[z] = random( )%xsize;
							ystarts[z] = random( )%ysize;
							objects[z] = new robots( (char *)names[z].data( ),*this,z,
								config,botteams[z],false );
							QObject::connect( objects[z],SIGNAL( armorchanged( int ) ),
								binfo[z],SLOT( armorupdated( int ) ) );
							QObject::connect( binfo[z], SIGNAL( changeinset( bool ) ),
								objects[z], SLOT( setextragfx( bool ) ) );
							QObject::connect( objects[z],SIGNAL( fuelchanged( int,int ) ),
								binfo[z],SLOT( updatefuel( int,int ) ) );
							QObject::connect( objects[z],SIGNAL( messagechanged( char * ) ),
								binfo[z],SLOT( newmessage( char * ) ) );
						}
						else
						{
							objects[z] = new screenobject( );
							fightswon[z] = roundsrun;
						}
					}
					else
					{
						delete objects[z];
						objects[z] = new screenobject( );
					}
				break;
				case 2 :
					int x = whichobject;
					int x2 = z;
					objects[x2]->eraseobject( mydrw );
					if( objects[x2]->returntype( ) == 1 )
					{
						if( objects[x]->getowner( ) < 8 && x2 != objects[x]->getowner( ) )
							fightswon[objects[x]->getowner( )]++;
						checkwin = true;
						//Calc X and Y position
						xstarts[x2] = random( )%xsize;
						ystarts[x2] = random( )%ysize;
						objects[x2] = new robots( (char *)names[x2].data( ),*this,x2,
							config,botteams[x2],false );
						QObject::connect( objects[x2],SIGNAL( armorchanged( int ) ),
							binfo[x2],SLOT( armorupdated( int ) ) );
						QObject::connect( binfo[x2], SIGNAL( changeinset( bool ) ),
							objects[x2], SLOT( setextragfx( bool ) ) );
						QObject::connect( objects[x2],SIGNAL( fuelchanged( int,int ) ),
							binfo[x2],SLOT( updatefuel( int,int ) ) );
						QObject::connect( objects[x2],SIGNAL( messagechanged( char * ) ),
							binfo[x2],SLOT( newmessage( char * ) ) );
					}
					else
					{
						delete objects[x2];
						objects[x2] = new screenobject( );
					}
				break;
			}
		}
	}
	int xxx;
	for ( xxx=254;xxx > 128;xxx-- )
	{
		if( objects[xxx]->returntype( ) == doesnotexist )
		{
			delete objects[xxx];
			objects[xxx] = new explosion( x,y,*this );
			break;
		}
	}
}

	/**
		* Gets xposition for one of the random start positions
		*/
/*int battlearea::getstartx( int bot )
{
	return xstarts[bot];
} */

	/**
		* Gets yposition for one o the random start positions
		*/
/*int battlearea::getstarty( int bot )
{
	return ystarts[bot];
} */

	/**
		* Dump RAM if pressed in debugwindow
		*/
void battlearea::dmem( )
{
	objects[7]->dumpRAM( );
}