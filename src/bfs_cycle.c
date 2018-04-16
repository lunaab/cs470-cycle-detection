#include <stdlib.h>
#include <stdio.h>
#include <igraph.h>
#include <mpi.h>
#include <pthread.h>

void bfs_cycle_detection(igraph_t* graph);
int search_for_cycles(igraph_t* graph, igraph_integer_t nmbrbl);
void swap(igraph_dqueue_t* a, igraph_dqueue_t* b);

igraph_integer_t is_cycle = 0;
igraph_integer_t is_finished = 0;
igraph_integer_t vertices = 10;
igraph_integer_t Level;

igraph_dqueue_t BBLQ_q;
igraph_dqueue_t BBLQ_prelevel;
igraph_dqueue_t BBLQ_id;
igraph_dqueue_t BBLQ_bl;

igraph_vector_t D;
igraph_vector_t id_vector;
igraph_vector_t bl_vector;

int mpi_rank;
int mpi_size;

int global_nmbrbl = 0;

pthread_mutex_t push_mutex = PTHREAD_MUTEX_INITIALIZER;

void* 
server_func (void* params)
{
    int recv;
    igraph_integer_t val;
    
    while (1)
    {
        MPI_Recv(&recv, 1, MPI_INT, MPI_ANY_SOURCE, NULL, MPI_COMM_WORLD, NULL);
        val = recv;
        
        pthread_mutex_lock(&push_mutex);
        igraph_dqueue_push(&NLQ, val);
        pthread_mutex_unlock(&push_mutex);
    }
    
    return NULL;
}


int
main (int argc, char* argv[])
{
    int provided;
    
    MPI_Init_thread(NULL, NULL, MPI_THREAD_MULTIPLE, &provided);
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
    
    pthread_t server;
    pthread_create(&server, NULL, server_func, NULL);

    igraph_integer_t i;
    igraph_integer_t holder = -1;
    igraph_vector_t edges;
    igraph_vector_t Owner;
    igraph_t graph;
    
    if (igraph_empty(&graph, vertices, IGRAPH_DIRECTED) == IGRAPH_EINVAL)
    {
        printf("Error: Failed to create graph\n");
    }
    
    igraph_vector_init(&edges, (vertices * 2));
    igraph_vector_init(&Owner, vertices);
    
    for(i = 0; i < vertices; i++) 
    {
        VECTOR(Owner)[i] = i % mpi_size;
        holder = (holder + 1);
        VECTOR(edges)[holder] = i;
        holder = (holder + 1);
        VECTOR(edges)[holder] = (i + 1) % vertices;
    }
    
    igraph_add_edges(&graph, &edges, NULL);
    
    FILE* fl = fopen("graph", "w+");
    igraph_write_graph_dot(&graph, fl);
    fclose(fl);
    
    printf("Number of Vertices: %d\n", igraph_vcount(&graph));
    printf("Number of Edges: %d\n", igraph_ecount(&graph));
    
    bfs_cycle_detection(&graph);
    
    if (is_cycle)
    {
        printf("Cycle Found\n");
    }

}

void
bfs_cycle_detection(igraph_t* graph)
{
    igraph_dqueue_t CLQ;
    igraph_dqueue_t NLQ;
    igraph_dqueue_t BLQ;
    
    igraph_vector_t Visited;
    igraph_vector_t neighbors;
    
    Level = 0;
    int send_val;
    igraph_integer_t nmbrbl = 0;
    igraph_integer_t v;
    igraph_integer_t i;
    
    igraph_dqueue_init(&CLQ, vertices);
    igraph_dqueue_init(&NLQ, vertices);
    igraph_dqueue_init(&BLQ, vertices);
    igraph_dqueue_init(&BBLQ_q, vertices);
    igraph_dqueue_init(&BBLQ_prelevel, vertices);
    igraph_dqueue_init(&BBLQ_id, vertices);
    igraph_dqueue_init(&BBLQ_bl, vertices);
    
    igraph_vector_init(&Visited, vertices);
    igraph_vector_init(&D, vertices);
    igraph_vector_init(&neighbors, vertices);
    igraph_vector_init(&id_vector, vertices);
    igraph_vector_init(&bl_vector, vertices);
    
    if (mpi_rank == 0)
    {
        pthread_mutex_lock(&push_mutex);
        igraph_dqueue_push(&NLQ, 0);
        pthread_mutex_unlock(&push_mutex);
    }
    
    while (!is_finished)
    {
        swap(&NLQ, &CLQ);
        igraph_dqueue_clear(&NLQ);
        nmbrbl = 0;
        //printf(
        while ( !igraph_dqueue_empty(&CLQ) )
        {
            v = (igraph_integer_t)igraph_dqueue_pop(&CLQ);
            printf("%d\n", v);
            if ( !(VECTOR(Visited)[v] == 1) )
            {
                VECTOR(Visited)[v] = 1;
                VECTOR(D)[v] = Level;
                printf("d(%d) = %d\n", v, Level);
                
                igraph_neighbors(graph, &neighbors, v, IGRAPH_OUT);
                for (i = 0; i < igraph_vector_size(&neighbors); i++)
                {
                    if (VECTOR(Owner)[i] == mpi_rank)
                    {
                        pthread_mutex_lock(&push_mutex);
                        igraph_dqueue_push(&NLQ, VECTOR(neighbors)[i]);
                        pthread_mutex_unlock(&push_mutex);
                    }
                    else
                    {
                        send_val = (int) VECTOR(neighbors)[i];
                        MPI_Send(&send_val, 1, MPI_INT,
                                 VECTOR(Owner)[VECTOR(neighbors)[i]], NULL, MPI_COMM_WORLD);
                    }
                }
            }
            else
            {
                if ((igraph_integer_t)VECTOR(D)[v] < Level)
                {
                    printf("%d < %d \n", (igraph_integer_t)VECTOR(D)[v], Level);
                    VECTOR(id_vector)[v] = 0;
                    VECTOR(bl_vector)[v] = 0;
                    igraph_dqueue_push(&BLQ, v);
                    nmbrbl = nmbrbl + 1;
                }
            }
        }
        
        //SYNCHRONIZE
        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Allreduce(&nmbrbl, &global_nmbrbl, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
        
        while ( !igraph_dqueue_empty(&BLQ) )
        {
            igraph_dqueue_push(&BBLQ_q, igraph_dqueue_pop(&BLQ));
            igraph_dqueue_push(&BBLQ_prelevel, Level-1);
            igraph_dqueue_push(&BBLQ_id, 0);
            igraph_dqueue_push(&BBLQ_bl, 0);
        }
        
        search_for_cycles(graph, global_nmbrbl);
        Level = Level + 1;
    }
    
    return;
}

int
search_for_cycles(igraph_t* graph, igraph_integer_t nmbrbl)
{
    igraph_integer_t q;
    igraph_integer_t prelevel;
    igraph_integer_t id;
    igraph_integer_t bl;
    igraph_integer_t i;
    
    igraph_vector_t neighbors;
    
    igraph_vector_init(&neighbors, vertices);

    while ( !igraph_dqueue_empty(&BBLQ_q) )
    {
        q = igraph_dqueue_pop(&BBLQ_q);
        prelevel = igraph_dqueue_pop(&BBLQ_prelevel);
        id = igraph_dqueue_pop(&BBLQ_id);
        bl = igraph_dqueue_pop(&BBLQ_bl);
        
        if ( VECTOR(D)[q] < Level )
        {
            //printf("Condition 1\n");
            if (q == id)
            {
                //printf("Condition 2\n");
                is_cycle = 1;
                is_finished = 1;
                return 1;
            }
            
            if (prelevel == Level - 1)
            {
                //printf("Condition 3\n");
                bl = bl + 1;
                if (bl > nmbrbl)
                {
                    //printf("Condition 4\n");
                    is_cycle = 1;
                    is_finished = 1;
                    return 1;
                }
            }
            
            if ( id > VECTOR(id_vector)[q] ||
                 (id == VECTOR(id_vector)[q] && bl > VECTOR(bl_vector)[q]))
            {
                //printf("Condition 5\n");
                VECTOR(id_vector)[q] = id;
                VECTOR(bl_vector)[q] = bl;
                igraph_neighbors(graph, &neighbors, q, IGRAPH_OUT);
                for (i = 0; i < igraph_vector_size(&neighbors); i++)
                {
                    igraph_dqueue_push(&BBLQ_q, VECTOR(neighbors)[i]);
                    igraph_dqueue_push(&BBLQ_prelevel, VECTOR(D)[q]);
                    igraph_dqueue_push(&BBLQ_id, id);
                    igraph_dqueue_push(&BBLQ_bl, bl);
                }
            }
        }
    }
    
}

void
swap(igraph_dqueue_t* a, igraph_dqueue_t* b)
{
    igraph_dqueue_t tmp = *a;
    *a = *b;
    *b = tmp;
}
