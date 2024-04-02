/**
 */
package at.jku.se.ecorexes.ecoreXES;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Feature And Class</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link at.jku.se.ecorexes.ecoreXES.FeatureAndClass#getClass_ <em>Class</em>}</li>
 *   <li>{@link at.jku.se.ecorexes.ecoreXES.FeatureAndClass#getFeature <em>Feature</em>}</li>
 * </ul>
 *
 * @see at.jku.se.ecorexes.ecoreXES.EcoreXESPackage#getFeatureAndClass()
 * @model
 * @generated
 */
public interface FeatureAndClass extends Attributes {
	/**
	 * Returns the value of the '<em><b>Class</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Class</em>' reference.
	 * @see #setClass(JavaClass)
	 * @see at.jku.se.ecorexes.ecoreXES.EcoreXESPackage#getFeatureAndClass_Class()
	 * @model required="true"
	 * @generated
	 */
	JavaClass getClass_();

	/**
	 * Sets the value of the '{@link at.jku.se.ecorexes.ecoreXES.FeatureAndClass#getClass_ <em>Class</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Class</em>' reference.
	 * @see #getClass_()
	 * @generated
	 */
	void setClass(JavaClass value);

	/**
	 * Returns the value of the '<em><b>Feature</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Feature</em>' reference.
	 * @see #setFeature(Feature)
	 * @see at.jku.se.ecorexes.ecoreXES.EcoreXESPackage#getFeatureAndClass_Feature()
	 * @model required="true"
	 * @generated
	 */
	Feature getFeature();

	/**
	 * Sets the value of the '{@link at.jku.se.ecorexes.ecoreXES.FeatureAndClass#getFeature <em>Feature</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Feature</em>' reference.
	 * @see #getFeature()
	 * @generated
	 */
	void setFeature(Feature value);

} // FeatureAndClass
