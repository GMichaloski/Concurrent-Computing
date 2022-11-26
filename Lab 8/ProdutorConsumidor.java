/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Codigo: Leitores e escritores usando monitores em Java */
/* -------------------------------------------------------------------*/
import Buffer.*;

//Aplicacao de exemplo--------------------------------------------------------
// Consumidor
class Consumidor extends Thread {
  int id; //identificador da thread
  int delay; //atraso bobo
  MonitorBuffer monitor;//objeto monitor para coordenar a lógica de execução das threads

  // Construtor
  Consumidor (int id, int delayTime, MonitorBuffer m) {
    this.id = id;
    this.delay = delayTime;
    this.monitor = m;
  }

  // Método executado pela thread
  public void run () {
    try {
      for (;;) {
        this.monitor.tentaRetirar(this.id);
        sleep(this.delay); 
      }
    } catch (InterruptedException e) { return; }
  }
}

//--------------------------------------------------------
// Produtor
class Produtor extends Thread {
  int id; //identificador da thread
  int delay; //atraso bobo...
  MonitorBuffer monitor; //objeto monitor para coordenar a lógica de execução das threads

  // Construtor
  Produtor (int id, int delayTime, MonitorBuffer m) {
    this.id = id;
    this.delay = delayTime;
    this.monitor = m;
  }

  // Método executado pela thread
  public void run () {
    try {
      for (;;) {
        this.monitor.tentaInserir(this.id); 
        sleep(this.delay); //atraso bobo...
      }
    } catch (InterruptedException e) { return; }
  }
}

//--------------------------------------------------------
// Classe principal
class ProdutorConsumidor {
  static final int C = 1;
  static final int P = 4;

  public static void main (String[] args) {
    int i;
    MonitorBuffer monitor = new MonitorBuffer();            // Monitor (objeto compartilhado entre produtores e consumidores)
    Consumidor[] l = new Consumidor[C];       // Threads leitores
    Produtor[] e = new Produtor[P];   // Threads escritores

    //inicia o log de saida
    System.out.println ("import verificaLE");
    System.out.println ("le = verificaLE.LE()");
    
    for (i=0; i<C; i++) {
       l[i] = new Consumidor(i+1, (i+1)*500, monitor);
       l[i].start(); 
    }
    for (i=0; i<P; i++) {
       e[i] = new Produtor(i+1, (i+1)*500, monitor);
       e[i].start(); 
    }
  }
}
