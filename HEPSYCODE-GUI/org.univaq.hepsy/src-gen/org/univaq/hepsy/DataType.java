/**
 */
package org.univaq.hepsy;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import org.eclipse.emf.common.util.Enumerator;

/**
 * <!-- begin-user-doc -->
 * A representation of the literals of the enumeration '<em><b>Data Type</b></em>',
 * and utility methods for working with them.
 * <!-- end-user-doc -->
 * @see org.univaq.hepsy.HepsyPackage#getDataType()
 * @model
 * @generated
 */
public enum DataType implements Enumerator {
	/**
	 * The '<em><b>Sc bit</b></em>' literal object.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #SC_BIT_VALUE
	 * @generated
	 * @ordered
	 */
	SC_BIT(0, "sc_bit", "sc_bit"),
	/**
	 * The '<em><b>Sc logic</b></em>' literal object.
	 * <!-- begin-user-doc -->
	* <!-- end-user-doc -->
	 * @see #SC_LOGIC_VALUE
	 * @generated
	 * @ordered
	 */
	SC_LOGIC(1, "sc_logic", "sc_logic"),
	/**
	 * The '<em><b>Sc int</b></em>' literal object.
	 * <!-- begin-user-doc -->
	* <!-- end-user-doc -->
	 * @see #SC_INT_VALUE
	 * @generated
	 * @ordered
	 */
	SC_INT(2, "sc_int", "sc_int"),
	/**
	 * The '<em><b>Sc uint</b></em>' literal object.
	 * <!-- begin-user-doc -->
	* <!-- end-user-doc -->
	 * @see #SC_UINT_VALUE
	 * @generated
	 * @ordered
	 */
	SC_UINT(3, "sc_uint", "sc_uint"),
	/**
	 * The '<em><b>Sc bigint</b></em>' literal object.
	 * <!-- begin-user-doc -->
	* <!-- end-user-doc -->
	 * @see #SC_BIGINT_VALUE
	 * @generated
	 * @ordered
	 */
	SC_BIGINT(4, "sc_bigint", "sc_bigint"),
	/**
	 * The '<em><b>Sc biguint</b></em>' literal object.
	 * <!-- begin-user-doc -->
	* <!-- end-user-doc -->
	 * @see #SC_BIGUINT_VALUE
	 * @generated
	 * @ordered
	 */
	SC_BIGUINT(5, "sc_biguint", "sc_biguint"),
	/**
	 * The '<em><b>Sc bv</b></em>' literal object.
	 * <!-- begin-user-doc -->
	* <!-- end-user-doc -->
	 * @see #SC_BV_VALUE
	 * @generated
	 * @ordered
	 */
	SC_BV(6, "sc_bv", "sc_bv"),
	/**
	 * The '<em><b>Sc lv</b></em>' literal object.
	 * <!-- begin-user-doc -->
	* <!-- end-user-doc -->
	 * @see #SC_LV_VALUE
	 * @generated
	 * @ordered
	 */
	SC_LV(7, "sc_lv", "sc_lv"),
	/**
	 * The '<em><b>Sc fixed</b></em>' literal object.
	 * <!-- begin-user-doc -->
	* <!-- end-user-doc -->
	 * @see #SC_FIXED_VALUE
	 * @generated
	 * @ordered
	 */
	SC_FIXED(8, "sc_fixed", "sc_fixed"),
	/**
	 * The '<em><b>Sc ufixed</b></em>' literal object.
	 * <!-- begin-user-doc -->
	* <!-- end-user-doc -->
	 * @see #SC_UFIXED_VALUE
	 * @generated
	 * @ordered
	 */
	SC_UFIXED(9, "sc_ufixed", "sc_ufixed"),
	/**
	 * The '<em><b>Sc fix</b></em>' literal object.
	 * <!-- begin-user-doc -->
	* <!-- end-user-doc -->
	 * @see #SC_FIX_VALUE
	 * @generated
	 * @ordered
	 */
	SC_FIX(10, "sc_fix", "sc_fix"),
	/**
	 * The '<em><b>Sc ufix</b></em>' literal object.
	 * <!-- begin-user-doc -->
	* <!-- end-user-doc -->
	 * @see #SC_UFIX_VALUE
	 * @generated
	 * @ordered
	 */
	SC_UFIX(11, "sc_ufix", "sc_ufix");

	/**
	 * The '<em><b>Sc bit</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #SC_BIT
	 * @model name="sc_bit"
	 * @generated
	 * @ordered
	 */
	public static final int SC_BIT_VALUE = 0;

	/**
	 * The '<em><b>Sc logic</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #SC_LOGIC
	 * @model name="sc_logic"
	 * @generated
	 * @ordered
	 */
	public static final int SC_LOGIC_VALUE = 1;

	/**
	 * The '<em><b>Sc int</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #SC_INT
	 * @model name="sc_int"
	 * @generated
	 * @ordered
	 */
	public static final int SC_INT_VALUE = 2;

	/**
	 * The '<em><b>Sc uint</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #SC_UINT
	 * @model name="sc_uint"
	 * @generated
	 * @ordered
	 */
	public static final int SC_UINT_VALUE = 3;

	/**
	 * The '<em><b>Sc bigint</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #SC_BIGINT
	 * @model name="sc_bigint"
	 * @generated
	 * @ordered
	 */
	public static final int SC_BIGINT_VALUE = 4;

	/**
	 * The '<em><b>Sc biguint</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #SC_BIGUINT
	 * @model name="sc_biguint"
	 * @generated
	 * @ordered
	 */
	public static final int SC_BIGUINT_VALUE = 5;

	/**
	 * The '<em><b>Sc bv</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #SC_BV
	 * @model name="sc_bv"
	 * @generated
	 * @ordered
	 */
	public static final int SC_BV_VALUE = 6;

	/**
	 * The '<em><b>Sc lv</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #SC_LV
	 * @model name="sc_lv"
	 * @generated
	 * @ordered
	 */
	public static final int SC_LV_VALUE = 7;

	/**
	 * The '<em><b>Sc fixed</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #SC_FIXED
	 * @model name="sc_fixed"
	 * @generated
	 * @ordered
	 */
	public static final int SC_FIXED_VALUE = 8;

	/**
	 * The '<em><b>Sc ufixed</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #SC_UFIXED
	 * @model name="sc_ufixed"
	 * @generated
	 * @ordered
	 */
	public static final int SC_UFIXED_VALUE = 9;

	/**
	 * The '<em><b>Sc fix</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #SC_FIX
	 * @model name="sc_fix"
	 * @generated
	 * @ordered
	 */
	public static final int SC_FIX_VALUE = 10;

	/**
	 * The '<em><b>Sc ufix</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #SC_UFIX
	 * @model name="sc_ufix"
	 * @generated
	 * @ordered
	 */
	public static final int SC_UFIX_VALUE = 11;

	/**
	 * An array of all the '<em><b>Data Type</b></em>' enumerators.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private static final DataType[] VALUES_ARRAY = new DataType[] { SC_BIT, SC_LOGIC, SC_INT, SC_UINT, SC_BIGINT,
			SC_BIGUINT, SC_BV, SC_LV, SC_FIXED, SC_UFIXED, SC_FIX, SC_UFIX, };

	/**
	 * A public read-only list of all the '<em><b>Data Type</b></em>' enumerators.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public static final List<DataType> VALUES = Collections.unmodifiableList(Arrays.asList(VALUES_ARRAY));

	/**
	 * Returns the '<em><b>Data Type</b></em>' literal with the specified literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param literal the literal.
	 * @return the matching enumerator or <code>null</code>.
	 * @generated
	 */
	public static DataType get(String literal) {
		for (int i = 0; i < VALUES_ARRAY.length; ++i) {
			DataType result = VALUES_ARRAY[i];
			if (result.toString().equals(literal)) {
				return result;
			}
		}
		return null;
	}

	/**
	 * Returns the '<em><b>Data Type</b></em>' literal with the specified name.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param name the name.
	 * @return the matching enumerator or <code>null</code>.
	 * @generated
	 */
	public static DataType getByName(String name) {
		for (int i = 0; i < VALUES_ARRAY.length; ++i) {
			DataType result = VALUES_ARRAY[i];
			if (result.getName().equals(name)) {
				return result;
			}
		}
		return null;
	}

	/**
	 * Returns the '<em><b>Data Type</b></em>' literal with the specified integer value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the integer value.
	 * @return the matching enumerator or <code>null</code>.
	 * @generated
	 */
	public static DataType get(int value) {
		switch (value) {
		case SC_BIT_VALUE:
			return SC_BIT;
		case SC_LOGIC_VALUE:
			return SC_LOGIC;
		case SC_INT_VALUE:
			return SC_INT;
		case SC_UINT_VALUE:
			return SC_UINT;
		case SC_BIGINT_VALUE:
			return SC_BIGINT;
		case SC_BIGUINT_VALUE:
			return SC_BIGUINT;
		case SC_BV_VALUE:
			return SC_BV;
		case SC_LV_VALUE:
			return SC_LV;
		case SC_FIXED_VALUE:
			return SC_FIXED;
		case SC_UFIXED_VALUE:
			return SC_UFIXED;
		case SC_FIX_VALUE:
			return SC_FIX;
		case SC_UFIX_VALUE:
			return SC_UFIX;
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
	private DataType(int value, String name, String literal) {
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

} //DataType
