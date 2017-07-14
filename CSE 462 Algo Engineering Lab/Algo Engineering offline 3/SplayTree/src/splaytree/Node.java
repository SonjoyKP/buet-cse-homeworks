/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package splaytree;


/**
 *
 * @author sonjoy
 */
public class Node {
    
    public int key;
    public Node leftNode,rightNode,parentNode;
    
    public Node()
    {
        
    }

    public Node(int x){
        key=x;
        leftNode=null;
        rightNode=null;
        parentNode=null;
    }
    
    
    
}
