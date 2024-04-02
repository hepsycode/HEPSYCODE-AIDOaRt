/**
 */
package at.jku.se.ecorexes.ecoreXES.impl;

import at.jku.se.ecorexes.ecoreXES.EcoreXESPackage;
import at.jku.se.ecorexes.ecoreXES.Feature;
import at.jku.se.ecorexes.ecoreXES.FeatureAndClass;
import at.jku.se.ecorexes.ecoreXES.JavaClass;

import org.eclipse.emf.common.notify.Notification;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Feature And Class</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link at.jku.se.ecorexes.ecoreXES.impl.FeatureAndClassImpl#getClass_ <em>Class</em>}</li>
 *   <li>{@link at.jku.se.ecorexes.ecoreXES.impl.FeatureAndClassImpl#getFeature <em>Feature</em>}</li>
 * </ul>
 *
 * @generated
 */
public class FeatureAndClassImpl extends AttributesImpl implements FeatureAndClass {
	/**
	 * The cached value of the '{@link #getClass_() <em>Class</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getClass_()
	 * @generated
	 * @ordered
	 */
	protected JavaClass class_;

	/**
	 * The cached value of the '{@link #getFeature() <em>Feature</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getFeature()
	 * @generated
	 * @ordered
	 */
	protected Feature feature;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected FeatureAndClassImpl() {
		super();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	protected EClass eStaticClass() {
		return EcoreXESPackage.Literals.FEATURE_AND_CLASS;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public JavaClass getClass_() {
		if (class_ != null && class_.eIsProxy()) {
			InternalEObject oldClass = (InternalEObject) class_;
			class_ = (JavaClass) eResolveProxy(oldClass);
			if (class_ != oldClass) {
				if (eNotificationRequired())
					eNotify(new ENotificationImpl(this, Notification.RESOLVE, EcoreXESPackage.FEATURE_AND_CLASS__CLASS,
							oldClass, class_));
			}
		}
		return class_;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public JavaClass basicGetClass() {
		return class_;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setClass(JavaClass newClass) {
		JavaClass oldClass = class_;
		class_ = newClass;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, EcoreXESPackage.FEATURE_AND_CLASS__CLASS, oldClass,
					class_));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Feature getFeature() {
		if (feature != null && feature.eIsProxy()) {
			InternalEObject oldFeature = (InternalEObject) feature;
			feature = (Feature) eResolveProxy(oldFeature);
			if (feature != oldFeature) {
				if (eNotificationRequired())
					eNotify(new ENotificationImpl(this, Notification.RESOLVE,
							EcoreXESPackage.FEATURE_AND_CLASS__FEATURE, oldFeature, feature));
			}
		}
		return feature;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Feature basicGetFeature() {
		return feature;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setFeature(Feature newFeature) {
		Feature oldFeature = feature;
		feature = newFeature;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, EcoreXESPackage.FEATURE_AND_CLASS__FEATURE,
					oldFeature, feature));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public Object eGet(int featureID, boolean resolve, boolean coreType) {
		switch (featureID) {
		case EcoreXESPackage.FEATURE_AND_CLASS__CLASS:
			if (resolve)
				return getClass_();
			return basicGetClass();
		case EcoreXESPackage.FEATURE_AND_CLASS__FEATURE:
			if (resolve)
				return getFeature();
			return basicGetFeature();
		}
		return super.eGet(featureID, resolve, coreType);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public void eSet(int featureID, Object newValue) {
		switch (featureID) {
		case EcoreXESPackage.FEATURE_AND_CLASS__CLASS:
			setClass((JavaClass) newValue);
			return;
		case EcoreXESPackage.FEATURE_AND_CLASS__FEATURE:
			setFeature((Feature) newValue);
			return;
		}
		super.eSet(featureID, newValue);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public void eUnset(int featureID) {
		switch (featureID) {
		case EcoreXESPackage.FEATURE_AND_CLASS__CLASS:
			setClass((JavaClass) null);
			return;
		case EcoreXESPackage.FEATURE_AND_CLASS__FEATURE:
			setFeature((Feature) null);
			return;
		}
		super.eUnset(featureID);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public boolean eIsSet(int featureID) {
		switch (featureID) {
		case EcoreXESPackage.FEATURE_AND_CLASS__CLASS:
			return class_ != null;
		case EcoreXESPackage.FEATURE_AND_CLASS__FEATURE:
			return feature != null;
		}
		return super.eIsSet(featureID);
	}

} //FeatureAndClassImpl
