#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

typedef struct ACTIVITY
{
	int fromId;
	int toId;
	int early;
	int late;
	int ok;
	int weight;

} ACTIVITY , * activity;

typedef struct VERTEX
{
	int early;
	int late;
	int ok;
	int weight;
	int size_from ;
	ACTIVITY** link_from ;
	int size_to;
	ACTIVITY** link_to;
} VERTEX , * vertex;

int vertex_max;
VERTEX *vertex_buffer;
int line_size;
activity line_buf;
VERTEX* GetVertex( int vertex_ID )
{
	if( vertex_max <= vertex_ID )
	{
		VERTEX* buf = vertex_buffer;
		vertex_buffer = ( VERTEX* ) malloc( sizeof( VERTEX ) * ( vertex_ID + 1 ) );
		memset( vertex_buffer , 0 , sizeof( VERTEX ) * ( vertex_ID + 1 ) );
		if( buf != NULL )
		{
			memcpy( vertex_buffer , buf , sizeof( VERTEX ) * vertex_max );
			free( buf );
		}
		vertex_max = vertex_ID + 1 ;
	}
	return vertex_buffer + vertex_ID ;
}
//
activity* VertexAddLink( activity* buf , int* bufSize , activity link )
{
	activity * bufBack = buf;
	int n = *bufSize + 1;
	buf = ( activity* ) malloc( sizeof( activity* ) * n );
	memset( buf , 0 , sizeof( activity* ) * n );
	if( NULL != bufBack )
	{
		memcpy( buf , bufBack , sizeof( VERTEX* ) *( *bufSize ));
		free( bufBack );
	}
	buf[*bufSize] = link;
	(*bufSize) = n ;
	return buf;
}

void AddLink( int lineId , int srcId , int toId , int weight )
{
	VERTEX* vertex;
	ACTIVITY* link = line_buf + lineId;
	vertex = GetVertex( srcId );
	vertex->link_to = VertexAddLink( vertex->link_to , &vertex->size_to , link );
	vertex = GetVertex( toId );
	vertex->link_from = VertexAddLink( vertex->link_from , &vertex->size_from , link );
    link->fromId = srcId;
	link->toId = toId;
	link->weight = weight;
}

void RemoveBuffer()
{
	vertex vertex;
	int k;
	if( line_buf != NULL )
	{
		free( line_buf );
	}
	line_buf = NULL;
	line_size = 0;
	if( vertex_buffer != NULL )
	{
		for( k = 0; k < vertex_max; ++k )
		{
			vertex = vertex_buffer + k;
			if( NULL != vertex->link_from )
				free( vertex->link_from );
			if( NULL != vertex->link_to )
				free( vertex->link_to );
		}
		free( vertex_buffer );
	}
	vertex_buffer = NULL;
	vertex_max = 0;
}

int keyin( )
{
	char ch[1024];
	char* str;
	int a , b , c , id;
	int i;
	scanf( "%d" , &a );
	line_size = a;
	if( line_size <= 0 )
	{
		printf( "key line count = 0 error¡G%s" , ch );
		return 0;
	}
	line_buf = ( activity ) malloc( sizeof( ACTIVITY ) * line_size );
	memset( line_buf , 0 , sizeof( ACTIVITY ) * line_size );
	for( i = 0; i < line_size; ++i )
	{
	    scanf( "%d %d %d %d\n" , &id , &a , &b , &c );
        AddLink( id , a , b , c );
	}
	return 1;
}
int AddTask( int* taskBuf , int taskPosition , int toId )
{
	int i;
	for( i = 0; i < taskPosition; ++i )
		if( toId == taskBuf[i] )
			return taskPosition;
	taskBuf[taskPosition] = toId;
	return taskPosition + 1;
}
int GetStartID()
{
	int s = 0 ;
	while( 1 )
	{
		if( vertex_buffer[s].size_from == 0 )
			return s;
		s = vertex_buffer[s].link_from[0]->fromId;
	}
	return s;
}
int GetEndID()
{
	int s = 0;
	while( 1 )
	{
		if( vertex_buffer[s].size_to == 0 )
		{
		    return s;
		}
		s = vertex_buffer[s].link_to[0]->toId;
	}
	return s;
}
void Topology( int start )
{
	int taskPosition;
	int i , u;
	int toid , from;
	int* task;
	int weight;
	vertex vertex;
	activity link ;
	task = ( int* ) malloc( sizeof( int ) * line_size );
	memset( task , 0 , sizeof( int ) * line_size );
	taskPosition = AddTask( task , 0 , GetStartID() );
	while( taskPosition > 0 )
	{
		taskPosition--;
		u = task[taskPosition];
		vertex = &vertex_buffer[u];
		for( i = 0; i < vertex->size_to ; ++i )
		{
			link = vertex->link_to[i];
			toid = link->toId;
			weight = vertex->early + link->weight;
			if( ( link->early == 0 ) || ( link->early < weight ) )
				link->early = weight - link->weight;
			if( ( vertex_buffer[toid].early == 0 ) || ( weight > vertex_buffer[toid].early ) )
			{
				vertex_buffer[toid].early = weight ;
				taskPosition = AddTask( task , taskPosition , link->toId );
			}
		}
	}
	taskPosition = AddTask( task , 0 , GetEndID() );
	vertex = vertex_buffer + GetEndID() ;
	vertex->late = vertex->early; ;
	while( taskPosition > 0 )
	{
		taskPosition--;
		u = task[taskPosition];
		vertex = &vertex_buffer[u];
		for( i = 0; i < vertex->size_from; ++i )
		{
			link = vertex->link_from[i];
			from = link->fromId ;
			weight = vertex->late - link->weight;
			if( ( link->late == 0 ) || ( link->late > weight ) )
				link->late = weight;
			if( ( vertex_buffer[from].late == 0 ) || ( weight < vertex_buffer[from].late ) )
            {
				vertex_buffer[from].late = weight;
				taskPosition = AddTask( task , taskPosition , link->fromId );
			}
		}
	}
	for( i = 0; i < line_size; ++i )
	{
		printf( "%d %d %d\n" , i , line_buf[i].early , line_buf[i].late );
	}
	int k = 0;
	for( i = 0; i < line_size; ++i )
	{
		if( line_buf[i].early == line_buf[i].late )
		{
			if( k == 0 )
			{
				printf( "%d" , i );
			}
			else
			{
				printf( " %d" , i );
			}
			++k;
		}
	}
	free( task );
}

int main()
{
	vertex_buffer = NULL;
	vertex_max = 0;
	line_size = 0 ;
	line_buf = NULL;
	activity link = NULL ;
	if( 0 == keyin() )
    {
        return 0 ;
    }
	Topology( 0 );
	RemoveBuffer();
	return 0;
}
