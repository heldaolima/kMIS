SYSTEM     = x86-64_linux
LIBFORMAT  = static_pic

CPLEXDIR      = /opt/ibm/ILOG/CPLEX_Studio2211/cplex/
CONCERTDIR    = /opt/ibm/ILOG/CPLEX_Studio2211/concert/

CXX=g++ -O0

CXXOPT=-m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD

CPLEXBINDIR   = $(CPLEXDIR)/bin/$(BINDIST)
CPLEXLIBDIR   = $(CPLEXDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CONCERTLIBDIR = $(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT)

CCLNDIRS  = -L$(CPLEXLIBDIR) -L$(CONCERTLIBDIR)
CLNDIRS   = -L$(CPLEXLIBDIR)
CCLNFLAGS = -lconcert -lilocplex -lcplex -lm -lpthread

CONCERTINCDIR = $(CONCERTDIR)/include
CPLEXINCDIR   = $(CPLEXDIR)/include

CCFLAGS = $(CCOPT) -I$(CPLEXINCDIR) -I$(CONCERTINCDIR)

DEPENDENCIES= subset.cpp input.cpp

m_aresta: m_aresta.o
	$(CXX) $(CCFLAGS) $(CCLNDIRS) -o m_aresta subset.o input.o m_aresta.o $(CCLNFLAGS)

m_aresta.o:
	$(CXX) -c $(CCFLAGS) subset.cpp input.cpp m_aresta.cpp 

clean:
	rm -rf *.out *.o
	rm m_aresta
