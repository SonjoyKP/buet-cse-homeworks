/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package splaytree;

import java.util.LinkedList;
import java.util.Queue;

/**
 *
 * @author sonjoy
 */
public class SplayTree {
    
    
    private class ReturnSplitedTwoTree
    {
        Node sl,sr;
    }
    
    
    
    
    
    public Node Root;

    public SplayTree() {
        Root=null;
    }
    
    
   
    public void  zig_left(Node x)
    {
        Node pNode,bNode;
        pNode=x.parentNode;
        bNode=x.rightNode;
        x.rightNode=pNode;
        x.parentNode=null;
        if(bNode!=null)
        {
            bNode.parentNode=pNode;
        }
        pNode.leftNode=bNode;
        pNode.parentNode=x;
    }
    public void zig_right(Node x)
    {
        Node pNode,bNode;
        pNode=x.parentNode;
        bNode=x.leftNode;
        x.leftNode=pNode;
        x.parentNode=null;
        
        if(bNode!=null)
        {
            bNode.parentNode=pNode;
        }
        pNode.rightNode=bNode;
        pNode.parentNode=x;
        
        
    }
    public void zig_zig_left(Node x)
    {
        Node pNode,gNode,ggpNode;
        Node bNode,cNode;
        
        pNode=x.parentNode;
        gNode=pNode.parentNode;
        bNode=x.rightNode;
        cNode=pNode.rightNode;
        ggpNode=gNode.parentNode;
        x.rightNode=pNode;
        pNode.parentNode=x;
        pNode.rightNode=gNode;
        gNode.parentNode=pNode;
        
        if(bNode!=null)
        {
            bNode.parentNode=pNode;
        }
        pNode.leftNode=bNode;
        
        if(cNode!=null)
        {
            cNode.parentNode=gNode;
        }
        gNode.leftNode=cNode;
        
        x.parentNode=ggpNode;
        
        if(ggpNode!=null)
        {
            if(ggpNode.leftNode==gNode)ggpNode.leftNode=x;
            else ggpNode.rightNode=x;
        }
        
    }
    
    public void zig_zig_right(Node x)
    {
        Node pNode,gNode,ggpNode;
        Node bNode,cNode;
        
        pNode=x.parentNode;
        gNode=pNode.parentNode;
        bNode=x.leftNode;
        cNode=pNode.leftNode;
        ggpNode=gNode.parentNode;
        x.leftNode=pNode;
        pNode.parentNode=x;
        pNode.leftNode=gNode;
        gNode.parentNode=pNode;
        
        if(bNode!=null)
        {
            bNode.parentNode=pNode;
        }
        pNode.rightNode=bNode;
        
        if(cNode!=null)
        {
            cNode.parentNode=gNode;
            
        }
        gNode.rightNode=cNode;
        
        x.parentNode=ggpNode;
        
        if(ggpNode!=null)
        {
            if(ggpNode.leftNode==gNode)ggpNode.leftNode=x;
            else ggpNode.rightNode=x;
            
             
        }
        
    }
    
    public void  zig_zag_left(Node x)
    {
        Node pNode,gNode,ggpNode;
        Node aNode,bNode;
        
        pNode=x.parentNode;
        gNode=pNode.parentNode;
        ggpNode=gNode.parentNode;
        aNode=x.leftNode;
        bNode=x.rightNode;
        
        x.leftNode=gNode;
        gNode.parentNode=x;
        x.rightNode=pNode;
        pNode.parentNode=x;
        
        if(aNode!=null)
        {
            aNode.parentNode=gNode;
            
        }
        gNode.rightNode=aNode;
        
        if(bNode!=null)
        {
            bNode.parentNode=pNode;
        }
        pNode.leftNode=bNode;
        
        x.parentNode=ggpNode;
        
        
        if(ggpNode!=null)
        {
            if(ggpNode.leftNode==gNode)ggpNode.leftNode=x;
            else ggpNode.rightNode=x;
            
             
        }
        
    }
    
    public void zig_zag_right(Node x)
    {
        Node pNode,gNode,ggpNode;
        Node aNode,bNode;
        
        pNode=x.parentNode;
        gNode=pNode.parentNode;
        ggpNode=gNode.parentNode;
        aNode=x.leftNode;
        bNode=x.rightNode;
        
        x.rightNode=gNode;
        gNode.parentNode=x;
        x.leftNode=pNode;
        pNode.parentNode=x;
        
        if(aNode!=null)
        {
            aNode.parentNode=pNode;
        }
        pNode.rightNode=aNode;
        
        if(bNode!=null)
        {
            bNode.parentNode=gNode;
        }
        gNode.leftNode=bNode;
        
        x.parentNode=ggpNode;
        
        if(ggpNode!=null)
        {
            if(ggpNode.leftNode==gNode)ggpNode.leftNode=x;
            else ggpNode.rightNode=x;
            
             
        }
         
    }
    
    
    public void singleRotation(Node x)
    {
        if(x.parentNode.leftNode==x)zig_left(x);
        else zig_right(x);
    }
    
    public void doubleRotation(Node x)
    {
        if(x.parentNode.leftNode==x && x.parentNode.parentNode.leftNode==x.parentNode)
        {
            zig_zig_left(x);
            return;
        }
        
        if(x.parentNode.leftNode==x && x.parentNode.parentNode.rightNode==x.parentNode)
        {
            zig_zag_left(x);
            return;
        }
        if(x.parentNode.rightNode==x && x.parentNode.parentNode.rightNode==x.parentNode)
        {
            zig_zig_right(x);
            return;
        }
        
        if(x.parentNode.rightNode==x && x.parentNode.parentNode.leftNode==x.parentNode)
        {
            zig_zag_right(x);
            return;
        }
    }
    
    public Node splay(Node rootNode ,int k)
    {
        
        if(rootNode==null)return rootNode;
        
        Node currentNode=rootNode;
        Node prevNode=null;
        
        while(currentNode!=null)
        {
            if(currentNode.key==k)break;
            prevNode=currentNode;
            if(k<currentNode.key)currentNode=currentNode.leftNode;
            else currentNode=currentNode.rightNode;
        }
        
        
     
        
        if(currentNode==null)
        {
            currentNode=prevNode;
            
        }
        
        
        Node Father=currentNode.parentNode;
        while(Father!=null)
        {
            if(Father.parentNode==null)singleRotation(currentNode);
            else doubleRotation(currentNode);
            Father=currentNode.parentNode;
        }
        
        return currentNode;
    }
    
    
    public searchResult search(Node rootNode,int k)
    {
        Node testRoot=splay(rootNode, k);
        searchResult retrunSearchResult=new searchResult();
        
        retrunSearchResult.CurrentRootAfterSearch=testRoot;
        if(testRoot!=null &&testRoot.key==k )
        {
            retrunSearchResult.foundOrNot=true;
        }
        else retrunSearchResult.foundOrNot=false;
        
        return retrunSearchResult;
    }
    
    
    public ReturnSplitedTwoTree split(Node rootNode,int x)
    {
        Node sl=null,sr=null;
        if(rootNode!=null)
        {
            Node testRootAfterSplay=splay(rootNode, x);
            
             if(testRootAfterSplay.key<x)
             {
                 sl=testRootAfterSplay;
                 sr=testRootAfterSplay.rightNode;
                 sl.rightNode=null;
             }
             else if(testRootAfterSplay.key==x)
             {
                 sl=testRootAfterSplay.leftNode;
                 sr=testRootAfterSplay.rightNode;
             }
             else if(testRootAfterSplay.key>x)
             {
                 sr=testRootAfterSplay;
                 sl=testRootAfterSplay.leftNode;
                 sr.leftNode=null;
             }
            
        }
        else
        {
            sl=null;
            sr=null;
           
        }
        ReturnSplitedTwoTree testReturnSplitedTwoTree=new ReturnSplitedTwoTree();
        testReturnSplitedTwoTree.sl=sl;
        testReturnSplitedTwoTree.sr=sr;
        return testReturnSplitedTwoTree;
    }
    
    
    
    public Node insert(Node rootNode,int k)
    {
        
        
        ReturnSplitedTwoTree testReturnSplitedTwoTree;
        testReturnSplitedTwoTree = split(rootNode, k);
        
        
        Node newRootNode=new Node();
        newRootNode.key=k;
        newRootNode.parentNode=null;
        newRootNode.leftNode=testReturnSplitedTwoTree.sl;
        newRootNode.rightNode=testReturnSplitedTwoTree.sr;
        
        if(testReturnSplitedTwoTree.sl!=null)testReturnSplitedTwoTree.sl.parentNode=newRootNode;
        if(testReturnSplitedTwoTree.sr!=null)testReturnSplitedTwoTree.sr.parentNode=newRootNode;
        
        
        return newRootNode;
        
//        if(rootNode==null)
//        {
//            
//            //System.out.println("entered in null condition");
//            rootNode=new Node();
//            rootNode.leftNode=null;
//            rootNode.rightNode=null;
//            rootNode.parentNode=null;
//            rootNode.key=k;
//            return rootNode;
//           
//        }
//        Node currentNode=rootNode;
//        Node anteriorNode=null;
//        int flag=0;//0 for left 1 right
//        while(currentNode!=null)
//        {
//           // System.out.println("entered in while loop");
//             
//            if(k==currentNode.key)return rootNode;
//            anteriorNode=currentNode;
//            if(k<currentNode.key)
//            {
//                flag=0;
//                currentNode=currentNode.leftNode;
//            }
//            else
//            {
//                flag=1;
//                currentNode=currentNode.rightNode;
//            }
//        }
//        currentNode=new Node();
//        currentNode.key=k;
//        currentNode.leftNode=null;
//        currentNode.rightNode=null;
//        currentNode.parentNode=anteriorNode;
//       // System.out.println("flag="+flag);
//        if(flag==0)anteriorNode.leftNode=currentNode;
//        else anteriorNode.rightNode=currentNode;
//        
//       // System.out.println("prent="+currentNode.parentNode.key);
//        
//        rootNode=splay(rootNode,currentNode.key);
        
        
        
                  
    }
    
    
    
    
    
    public void printTree(Node rootNode)
    {
       
        if (rootNode!=null)
        {
            System.out.print(rootNode.key+" ");
            printTree(rootNode.leftNode);
            printTree(rootNode.rightNode);
        }
        

        
    
    }
    
    public Node join(Node sl,Node sr,Node rootNode)
    {
        if(sl!=null)
        {
            search(sl, 1000000000);
            sl.rightNode=sr;
            if(sr!=null)
            {
                sr.parentNode=sl;
            }
            rootNode=sl;
            //search()
        }
        else
        {
            if(sr!=null)
            {
                rootNode=sr;
            }
            else rootNode=null;
        }
        return rootNode;
        
    }
    
    public Node delete(Node rootNode,int k)
    {
        rootNode=search(rootNode, k).CurrentRootAfterSearch;
        if(rootNode!=null &&rootNode.key==k)
        {
            Node sl=rootNode.leftNode;
            if(sl!=null)
            {
                sl.parentNode=null;
            }
            Node sr=rootNode.rightNode;
            if(sr!=null)
            {
                sr.parentNode=null;
            }
            rootNode=join(sl, sr, rootNode);
            
            
        }
        return rootNode;
        
        
    }

   
    
   
    
    
    
   
   
   
    
}
