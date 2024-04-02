/**
 */
package at.jku.se.ecorexes.ecoreXES;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import org.eclipse.emf.common.util.Enumerator;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Event Type</b></em>'.
 * <!-- end-user-doc -->
 * @see at.jku.se.ecorexes.ecoreXES.EcoreXESPackage#getEventType()
 * @model
 * @generated
 */
public enum EventType implements Enumerator {
	/**
	 * The '<em><b>SET</b></em>' literal object.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #SET_VALUE
	 * @generated
	 * @ordered
	 */
	SET(1, "SET", "SET"),
	/**
	 * The '<em><b>UNSET</b></em>' literal object.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #UNSET_VALUE
	 * @generated
	 * @ordered
	 */
	UNSET(2, "UNSET", "UNSET"),
	/**
	 * The '<em><b>ADD</b></em>' literal object.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #ADD_VALUE
	 * @generated
	 * @ordered
	 */
	ADD(3, "ADD", "ADD"),
	/**
	 * The '<em><b>REMOVE</b></em>' literal object.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #REMOVE_VALUE
	 * @generated
	 * @ordered
	 */
	REMOVE(4, "REMOVE", "REMOVE"),
	/**
	 * The '<em><b>ADD MANY</b></em>' literal object.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #ADD_MANY_VALUE
	 * @generated
	 * @ordered
	 */
	ADD_MANY(5, "ADD_MANY", "ADD_MANY"),
	/**
	 * The '<em><b>REMOVE MANY</b></em>' literal object.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #REMOVE_MANY_VALUE
	 * @generated
	 * @ordered
	 */
	REMOVE_MANY(6, "REMOVE_MANY", "REMOVE_MANY"),
	/**
	 * The '<em><b>MOVE</b></em>' literal object.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #MOVE_VALUE
	 * @generated
	 * @ordered
	 */
	MOVE(7, "MOVE", "MOVE"),
	/**
	 * The '<em><b>RESOLVE</b></em>' literal object.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #RESOLVE_VALUE
	 * @generated
	 * @ordered
	 */
	RESOLVE(9, "RESOLVE", "RESOLVE");

	/**
	 * The '<em><b>SET</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #SET
	 * @model
	 * @generated
	 * @ordered
	 */
	public static final int SET_VALUE = 1;

	/**
	 * The '<em><b>UNSET</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #UNSET
	 * @model
	 * @generated
	 * @ordered
	 */
	public static final int UNSET_VALUE = 2;

	/**
	 * The '<em><b>ADD</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #ADD
	 * @model
	 * @generated
	 * @ordered
	 */
	public static final int ADD_VALUE = 3;

	/**
	 * The '<em><b>REMOVE</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #REMOVE
	 * @model
	 * @generated
	 * @ordered
	 */
	public static final int REMOVE_VALUE = 4;

	/**
	 * The '<em><b>ADD MANY</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #ADD_MANY
	 * @model
	 * @generated
	 * @ordered
	 */
	public static final int ADD_MANY_VALUE = 5;

	/**
	 * The '<em><b>REMOVE MANY</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #REMOVE_MANY
	 * @model
	 * @generated
	 * @ordered
	 */
	public static final int REMOVE_MANY_VALUE = 6;

	/**
	 * The '<em><b>MOVE</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #MOVE
	 * @model
	 * @generated
	 * @ordered
	 */
	public static final int MOVE_VALUE = 7;

	/**
	 * The '<em><b>RESOLVE</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #RESOLVE
	 * @model
	 * @generated
	 * @ordered
	 */
	public static final int RESOLVE_VALUE = 9;

	/**
	 * An array of all the '<em><b>Event Type</b></em>' enumerators.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private static final EventType[] VALUES_ARRAY = new EventType[] { SET, UNSET, ADD, REMOVE, ADD_MANY, REMOVE_MANY,
			MOVE, RESOLVE, };

	/**
	 * A public read-only list of all the '<em><b>Event Type</b></em>' enumerators.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public static final List<EventType> VALUES = Collections.unmodifiableList(Arrays.asList(VALUES_ARRAY));

	/**
	 * Returns the '<em><b>Event Type</b></em>' literal with the specified literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param literal the literal.
	 * @return the matching enumerator or <code>null</code>.
	 * @generated
	 */
	public static EventType get(String literal) {
		for (int i = 0; i < VALUES_ARRAY.length; ++i) {
			EventType result = VALUES_ARRAY[i];
			if (result.toString().equals(literal)) {
				return result;
			}
		}
		return null;
	}

	/**
	 * Returns the '<em><b>Event Type</b></em>' literal with the specified name.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param name the name.
	 * @return the matching enumerator or <code>null</code>.
	 * @generated
	 */
	public static EventType getByName(String name) {
		for (int i = 0; i < VALUES_ARRAY.length; ++i) {
			EventType result = VALUES_ARRAY[i];
			if (result.getName().equals(name)) {
				return result;
			}
		}
		return null;
	}

	/**
	 * Returns the '<em><b>Event Type</b></em>' literal with the specified integer value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the integer value.
	 * @return the matching enumerator or <code>null</code>.
	 * @generated
	 */
	public static EventType get(int value) {
		switch (value) {
		case SET_VALUE:
			return SET;
		case UNSET_VALUE:
			return UNSET;
		case ADD_VALUE:
			return ADD;
		case REMOVE_VALUE:
			return REMOVE;
		case ADD_MANY_VALUE:
			return ADD_MANY;
		case REMOVE_MANY_VALUE:
			return REMOVE_MANY;
		case MOVE_VALUE:
			return MOVE;
		case RESOLVE_VALUE:
			return RESOLVE;
		}
		return null;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private final int value;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private final String name;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private final String literal;

	/**
	 * Only this class can construct instances.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private EventType(int value, String name, String literal) {
		this.value = value;
		this.name = name;
		this.literal = literal;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public int getValue() {
		return value;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public String getName() {
		return name;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public String getLiteral() {
		return literal;
	}

	/**
	 * Returns the literal value of the enumerator, which is its string representation.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public String toString() {
		return literal;
	}
}
