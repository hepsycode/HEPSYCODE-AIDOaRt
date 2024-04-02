/**
 */
package at.jku.se.ecorexes.ecoreXES.util;

import at.jku.se.ecorexes.ecoreXES.*;

import org.eclipse.emf.common.notify.Adapter;
import org.eclipse.emf.common.notify.Notifier;

import org.eclipse.emf.common.notify.impl.AdapterFactoryImpl;

import org.eclipse.emf.ecore.EObject;

/**
 * <!-- begin-user-doc -->
 * The <b>Adapter Factory</b> for the model.
 * It provides an adapter <code>createXXX</code> method for each class of the model.
 * <!-- end-user-doc -->
 * @see at.jku.se.ecorexes.ecoreXES.EcoreXESPackage
 * @generated
 */
public class EcoreXESAdapterFactory extends AdapterFactoryImpl {
	/**
	 * The cached model package.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected static EcoreXESPackage modelPackage;

	/**
	 * Creates an instance of the adapter factory.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EcoreXESAdapterFactory() {
		if (modelPackage == null) {
			modelPackage = EcoreXESPackage.eINSTANCE;
		}
	}

	/**
	 * Returns whether this factory is applicable for the type of the object.
	 * <!-- begin-user-doc -->
	 * This implementation returns <code>true</code> if the object is either the model's package or is an instance object of the model.
	 * <!-- end-user-doc -->
	 * @return whether this factory is applicable for the type of the object.
	 * @generated
	 */
	@Override
	public boolean isFactoryForType(Object object) {
		if (object == modelPackage) {
			return true;
		}
		if (object instanceof EObject) {
			return ((EObject) object).eClass().getEPackage() == modelPackage;
		}
		return false;
	}

	/**
	 * The switch that delegates to the <code>createXXX</code> methods.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected EcoreXESSwitch<Adapter> modelSwitch = new EcoreXESSwitch<Adapter>() {
		@Override
		public Adapter caseEvent(Event object) {
			return createEventAdapter();
		}

		@Override
		public Adapter caseLog(Log object) {
			return createLogAdapter();
		}

		@Override
		public Adapter caseAttributes(Attributes object) {
			return createAttributesAdapter();
		}

		@Override
		public Adapter caseFeatureAndClass(FeatureAndClass object) {
			return createFeatureAndClassAdapter();
		}

		@Override
		public Adapter caseFeature(Feature object) {
			return createFeatureAdapter();
		}

		@Override
		public Adapter caseJavaClass(JavaClass object) {
			return createJavaClassAdapter();
		}

		@Override
		public Adapter caseID(ID object) {
			return createIDAdapter();
		}

		@Override
		public Adapter caseReferenceValue(ReferenceValue object) {
			return createReferenceValueAdapter();
		}

		@Override
		public Adapter defaultCase(EObject object) {
			return createEObjectAdapter();
		}
	};

	/**
	 * Creates an adapter for the <code>target</code>.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param target the object to adapt.
	 * @return the adapter for the <code>target</code>.
	 * @generated
	 */
	@Override
	public Adapter createAdapter(Notifier target) {
		return modelSwitch.doSwitch((EObject) target);
	}

	/**
	 * Creates a new adapter for an object of class '{@link at.jku.se.ecorexes.ecoreXES.Event <em>Event</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see at.jku.se.ecorexes.ecoreXES.Event
	 * @generated
	 */
	public Adapter createEventAdapter() {
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link at.jku.se.ecorexes.ecoreXES.Log <em>Log</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see at.jku.se.ecorexes.ecoreXES.Log
	 * @generated
	 */
	public Adapter createLogAdapter() {
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link at.jku.se.ecorexes.ecoreXES.Attributes <em>Attributes</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see at.jku.se.ecorexes.ecoreXES.Attributes
	 * @generated
	 */
	public Adapter createAttributesAdapter() {
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link at.jku.se.ecorexes.ecoreXES.FeatureAndClass <em>Feature And Class</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see at.jku.se.ecorexes.ecoreXES.FeatureAndClass
	 * @generated
	 */
	public Adapter createFeatureAndClassAdapter() {
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link at.jku.se.ecorexes.ecoreXES.Feature <em>Feature</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see at.jku.se.ecorexes.ecoreXES.Feature
	 * @generated
	 */
	public Adapter createFeatureAdapter() {
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link at.jku.se.ecorexes.ecoreXES.JavaClass <em>Java Class</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see at.jku.se.ecorexes.ecoreXES.JavaClass
	 * @generated
	 */
	public Adapter createJavaClassAdapter() {
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link at.jku.se.ecorexes.ecoreXES.ID <em>ID</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see at.jku.se.ecorexes.ecoreXES.ID
	 * @generated
	 */
	public Adapter createIDAdapter() {
		return null;
	}

	/**
	 * Creates a new adapter for an object of class '{@link at.jku.se.ecorexes.ecoreXES.ReferenceValue <em>Reference Value</em>}'.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null so that we can easily ignore cases;
	 * it's useful to ignore a case when inheritance will catch all the cases anyway.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @see at.jku.se.ecorexes.ecoreXES.ReferenceValue
	 * @generated
	 */
	public Adapter createReferenceValueAdapter() {
		return null;
	}

	/**
	 * Creates a new adapter for the default case.
	 * <!-- begin-user-doc -->
	 * This default implementation returns null.
	 * <!-- end-user-doc -->
	 * @return the new adapter.
	 * @generated
	 */
	public Adapter createEObjectAdapter() {
		return null;
	}

} //EcoreXESAdapterFactory
