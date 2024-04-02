/**
 */
package at.jku.se.eclipse.emf.ecore.change;

import org.eclipse.emf.ecore.EObject;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Change</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link at.jku.se.eclipse.emf.ecore.change.Change#getTimeStamp <em>Time Stamp</em>}</li>
 * </ul>
 *
 * @see at.jku.se.eclipse.emf.ecore.change.ChangePackage#getChange()
 * @model
 * @generated
 */
public interface Change extends EObject {
	/**
	 * Returns the value of the '<em><b>Time Stamp</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Time Stamp</em>' attribute.
	 * @see #setTimeStamp(long)
	 * @see at.jku.se.eclipse.emf.ecore.change.ChangePackage#getChange_TimeStamp()
	 * @model
	 * @generated
	 */
	long getTimeStamp();

	/**
	 * Sets the value of the '{@link at.jku.se.eclipse.emf.ecore.change.Change#getTimeStamp <em>Time Stamp</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Time Stamp</em>' attribute.
	 * @see #getTimeStamp()
	 * @generated
	 */
	void setTimeStamp(long value);

} // Change
