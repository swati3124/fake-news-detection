/**
 * Created by mitshubh on 3/14/17.
 */
public class BinaryTree {

    class Node {
        int data;
        Node left;
        Node right;

        public Node(int val) {
            this.data=val;
            this.left=null;
            this.right=null;
        }
    }

    Node root;

    public void addNode(int val) {
        if (root==null) {
            root = new Node(val);
            return;
        }
        Node node = new Node(val);
        if (dir.equals("left")) {
            root.left = node;
        } else {
            root.right = node;
        }
    }

    public static void main(String[] args) {
        BinaryTree binaryTree = new BinaryTree();
        binaryTree.addNode(1);
        binaryTree.addNode(2);
        binaryTree.addNode(3);
        binaryTree.addNode(4);
        binaryTree.addNode(5);
        binaryTree.addNode(6);
    }
}
