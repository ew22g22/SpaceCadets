package me.ellis.barebonesextended.parser.codelet;

public interface ICodelet {
    /***
     * Generates and returns assembly code snippet depending on the type
     * of class implementing this interface.
     * @return Assembly code snippet
     */
    String getCode();

    /***
     * Type of codelet associated with the implementing class
     * @return Type of Codelet
     */
    //CodeletType getType();
}
