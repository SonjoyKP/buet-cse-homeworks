/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package splaytree;

import java.util.Scanner;
import java.util.concurrent.ThreadLocalRandom;

/**
 *
 * @author sonjoy
 */
public class MainClass {

    public static void main(String[] args) {

        Node RootNode = null;
        SplayTree testTree = new SplayTree();

        Scanner reader = new Scanner(System.in);
        int counter = 0;
        while (counter < 20) {
            counter++;
//            System.out.println("Enter a Choice: ");
//            System.out.println("    1.Insert(x)");
//            System.out.println("    2.Splay(x)");
//            System.out.println("    3.Search(x)");
//            System.out.println("    4.Delete(x)");
//            System.out.println("    5.Print(T)");
//            System.out.println("    6.Exit\n");
//            System.out.print("Enter Your Choice N=: ");
//            int n = reader.nextInt();

            int n = ThreadLocalRandom.current().nextInt(1, 4 + 1);

            if (n == 1) {
//                System.out.print("Enter the value of X: ");
//                int x = reader.nextInt();

                int x = ThreadLocalRandom.current().nextInt(0, 100 + 1);
                System.out.println("Inserting =" + x);
                RootNode = testTree.insert(RootNode, x);
                System.out.println("----Printing Tree-----");
                BTreePrinter.printNode(RootNode);
                System.out.println("------end------");

            } else if (n == 2) {
//                System.out.print("Enter the value of X: ");
//                int x = reader.nextInt();
                int x = ThreadLocalRandom.current().nextInt(0, 100 + 1);
                System.out.println("Splaying =" + x);
                RootNode = testTree.splay(RootNode, x);
                System.out.println("----Printing Tree-----");
                BTreePrinter.printNode(RootNode);
                System.out.println("------end------");
            } else if (n == 3) {
//                System.out.print("Enter the value of X: ");
//                int x = reader.nextInt();
                int x = ThreadLocalRandom.current().nextInt(0, 100 + 1);
                searchResult result;
                System.out.println("searching =" + x);
                result = testTree.search(RootNode, x);
                RootNode = result.CurrentRootAfterSearch;
                if (result.foundOrNot) {
                    System.out.println("Found the element=" + x);
                } else {
                    System.out.println("Not found the element");
                }
                System.out.println("----Printing Tree-----");
                BTreePrinter.printNode(RootNode);
                System.out.println("------end------");
            } else if (n == 4) {
//                System.out.print("Enter the value of X: ");
//                int x = reader.nextInt();
                int x = ThreadLocalRandom.current().nextInt(0, 100 + 1);
                System.out.println("deleting =" + x);
                RootNode = testTree.delete(RootNode, x);
                System.out.println("----Printing Tree-----");
                BTreePrinter.printNode(RootNode);
                System.out.println("------end------");
            } else if (n == 5) {
                System.out.println("----Printing Tree-----");
                BTreePrinter.printNode(RootNode);
                System.out.println("------end------");
            } else if (n == 6) {
                System.out.println("Exiting Program");
                break;
            }

        }
        System.out.println("----Printing Tree-----");
        BTreePrinter.printNode(RootNode);
        System.out.println("");
        // Reading from System.in

//        testTree.printTree(RootNode);
//        System.out.println("");
//        
//        RootNode=testTree.insert(RootNode,100);
//        
//        testTree.printTree(RootNode);
//        System.out.println("");
//        
//        RootNode=testTree.insert(RootNode,200);
//        RootNode=testTree.insert(RootNode,40);
//        
//        testTree.printTree(RootNode);
//        System.out.println("");
//        
//        RootNode=testTree.insert(RootNode,35);
//        RootNode=testTree.insert(RootNode,20);
//        RootNode=testTree.insert(RootNode,25);
//        
//        testTree.printTree(RootNode);
//        System.out.println("");
//        
//        
//        RootNode=testTree.search(RootNode,150);
//        if(RootNode.key==150)System.out.println("found");
//        else System.out.println("Not Found");
//        
//        testTree.printTree(RootNode);
//        System.out.println("");
//        BTreePrinter.printNode(RootNode);
//        
//        RootNode=testTree.delete(RootNode, 20);
//        
//        testTree.printTree(RootNode);
//        System.out.println("");
//        
//        BTreePrinter.printNode(RootNode);
        //testTree.insert(testTree.Root, 5);
    }
}
