package Buffer;

import java.util.Arrays;

public class MonitorBuffer {
    float[] array = new float[10];
    int quantidadeDeElementosNoBuffer = 0;
    int TAMANHODOBUFFER = 10;
    public MonitorBuffer(){
        for (int i=0; i < TAMANHODOBUFFER; i++){
            array[i] = 0;
        }
    }

    public synchronized void tentaInserir(int id){
        System.out.println(id + " quer inserir");
        try{
            while (quantidadeDeElementosNoBuffer == TAMANHODOBUFFER){
                System.out.println(id + " foi bloqueado!");
                wait();
                System.out.println(id + " foi desbloqueado!");
            }
            insere();

            System.out.println(id + " inseriu!");
            imprimeElementos();
            notify();
        }catch (InterruptedException e) {}

    }
    public synchronized void tentaRetirar(int id){
        System.out.println(id + " quer retirar!");
        try{
            while (quantidadeDeElementosNoBuffer == 0){
                System.out.println(id + " foi bloqueado!");
                wait();
                System.out.println(id + " foi desbloqueado!");
            }
            retira();
            System.out.println(id + " retirou!");
            imprimeElementos();
            notify();
        }catch (InterruptedException e) {}
    }
    private void imprimeElementos(){
        System.out.println( Arrays.toString(array));
    }

    private void insere()
    {
        for (int i =0; i < TAMANHODOBUFFER; i++){
            if (array[i] == 0){
                array[i] = 1;
                quantidadeDeElementosNoBuffer++;
                return;
            }
        }
    }

    private void retira(){
        for (int i =0; i < TAMANHODOBUFFER; i++){
            if (array[i] == 1){
                array[i] = 0;
                quantidadeDeElementosNoBuffer--;
                return;
            }
        }
    }
}
