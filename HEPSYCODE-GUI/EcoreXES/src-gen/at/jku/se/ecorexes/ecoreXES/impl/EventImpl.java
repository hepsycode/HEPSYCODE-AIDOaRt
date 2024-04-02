/**
 */
package at.jku.se.ecorexes.ecoreXES.impl;

import at.jku.se.ecorexes.ecoreXES.EcoreXESPackage;
import at.jku.se.ecorexes.ecoreXES.Event;
import at.jku.se.ecorexes.ecoreXES.EventType;
import at.jku.se.ecorexes.ecoreXES.FeatureAndClass;
import at.jku.se.ecorexes.ecoreXES.ID;
import at.jku.se.ecorexes.ecoreXES.ReferenceValue;

import java.util.Date;

import org.eclipse.emf.common.notify.Notification;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;
import org.eclipse.emf.ecore.impl.MinimalEObjectImpl;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Event</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link at.jku.se.ecorexes.ecoreXES.impl.EventImpl#isSet <em>Set</em>}</li>
 *   <li>{@link at.jku.se.ecorexes.ecoreXES.impl.EventImpl#getTimestamp <em>Timestamp</em>}</li>
 *   <li>{@link at.jku.se.ecorexes.ecoreXES.impl.EventImpl#getFatureAndClass <em>Fature And Class</em>}</li>
 *   <li>{@link at.jku.se.ecorexes.ecoreXES.impl.EventImpl#getId <em>Id</em>}</li>
 *   <li>{@link at.jku.se.ecorexes.ecoreXES.impl.EventImpl#getReferencevalue <em>Referencevalue</em>}</li>
 *   <li>{@link at.jku.se.ecorexes.ecoreXES.impl.EventImpl#getDataValue <em>Data Value</em>}</li>
 *   <li>{@link at.jku.se.ecorexes.ecoreXES.impl.EventImpl#getEventType <em>Event Type</em>}</li>
 * </ul>
 *
 * @generated
 */
public class EventImpl extends MinimalEObjectImpl.Container implements Event {
	/**
	 * The default value of the '{@link #isSet() <em>Set</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #isSet()
	 * @generated
	 * @ordered
	 */
	protected static final boolean SET_EDEFAULT = false;

	/**
	 * The cached value of the '{@link #isSet() <em>Set</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #isSet()
	 * @generated
	 * @ordered
	 */
	protected boolean set = SET_EDEFAULT;

	/**
	 * The default value of the '{@link #getTimestamp() <em>Timestamp</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getTimestamp()
	 * @generated
	 * @ordered
	 */
	protected static final Date TIMESTAMP_EDEFAULT = null;

	/**
	 * The cached value of the '{@link #getTimestamp() <em>Timestamp</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getTimestamp()
	 * @generated
	 * @ordered
	 */
	protected Date timestamp = TIMESTAMP_EDEFAULT;

	/**
	 * The cached value of the '{@link #getFatureAndClass() <em>Fature And Class</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getFatureAndClass()
	 * @generated
	 * @ordered
	 */
	protected FeatureAndClass fatureAndClass;

	/**
	 * The cached value of the '{@link #getId() <em>Id</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getId()
	 * @generated
	 * @ordered
	 */
	protected ID id;

	/**
	 * The cached value of the '{@link #getReferencevalue() <em>Referencevalue</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getReferencevalue()
	 * @generated
	 * @ordered
	 */
	protected ReferenceValue referencevalue;

	/**
	 * The default value of the '{@link #getDataValue() <em>Data Value</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getDataValue()
	 * @generated
	 * @ordered
	 */
	protected static final String DATA_VALUE_EDEFAULT = null;

	/**
	 * The cached value of the '{@link #getDataValue() <em>Data Value</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getDataValue()
	 * @generated
	 * @ordered
	 */
	protected String dataValue = DATA_VALUE_EDEFAULT;

	/**
	 * The default value of the '{@link #getEventType() <em>Event Type</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getEventType()
	 * @generated
	 * @ordered
	 */
	protected static final EventType EVENT_TYPE_EDEFAULT = EventType.SET;

	/**
	 * The cached value of the '{@link #getEventType() <em>Event Type</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getEventType()
	 * @generated
	 * @ordered
	 */
	protected EventType eventType = EVENT_TYPE_EDEFAULT;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected EventImpl() {
		super();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	protected EClass eStaticClass() {
		return EcoreXESPackage.Literals.EVENT;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public boolean isSet() {
		return set;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setSet(boolean newSet) {
		boolean oldSet = set;
		set = newSet;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, EcoreXESPackage.EVENT__SET, oldSet, set));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Date getTimestamp() {
		return timestamp;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setTimestamp(Date newTimestamp) {
		Date oldTimestamp = timestamp;
		timestamp = newTimestamp;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, EcoreXESPackage.EVENT__TIMESTAMP, oldTimestamp,
					timestamp));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public FeatureAndClass getFatureAndClass() {
		if (fatureAndClass != null && fatureAndClass.eIsProxy()) {
			InternalEObject oldFatureAndClass = (InternalEObject) fatureAndClass;
			fatureAndClass = (FeatureAndClass) eResolveProxy(oldFatureAndClass);
			if (fatureAndClass != oldFatureAndClass) {
				if (eNotificationRequired())
					eNotify(new ENotificationImpl(this, Notification.RESOLVE, EcoreXESPackage.EVENT__FATURE_AND_CLASS,
							oldFatureAndClass, fatureAndClass));
			}
		}
		return fatureAndClass;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public FeatureAndClass basicGetFatureAndClass() {
		return fatureAndClass;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setFatureAndClass(FeatureAndClass newFatureAndClass) {
		FeatureAndClass oldFatureAndClass = fatureAndClass;
		fatureAndClass = newFatureAndClass;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, EcoreXESPackage.EVENT__FATURE_AND_CLASS,
					oldFatureAndClass, fatureAndClass));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public ID getId() {
		if (id != null && id.eIsProxy()) {
			InternalEObject oldId = (InternalEObject) id;
			id = (ID) eResolveProxy(oldId);
			if (id != oldId) {
				if (eNotificationRequired())
					eNotify(new ENotificationImpl(this, Notification.RESOLVE, EcoreXESPackage.EVENT__ID, oldId, id));
			}
		}
		return id;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public ID basicGetId() {
		return id;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setId(ID newId) {
		ID oldId = id;
		id = newId;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, EcoreXESPackage.EVENT__ID, oldId, id));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public ReferenceValue getReferencevalue() {
		if (referencevalue != null && referencevalue.eIsProxy()) {
			InternalEObject oldReferencevalue = (InternalEObject) referencevalue;
			referencevalue = (ReferenceValue) eResolveProxy(oldReferencevalue);
			if (referencevalue != oldReferencevalue) {
				if (eNotificationRequired())
					eNotify(new ENotificationImpl(this, Notification.RESOLVE, EcoreXESPackage.EVENT__REFERENCEVALUE,
							oldReferencevalue, referencevalue));
			}
		}
		return referencevalue;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public ReferenceValue basicGetReferencevalue() {
		return referencevalue;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setReferencevalue(ReferenceValue newReferencevalue) {
		ReferenceValue oldReferencevalue = referencevalue;
		referencevalue = newReferencevalue;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, EcoreXESPackage.EVENT__REFERENCEVALUE,
					oldReferencevalue, referencevalue));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public String getDataValue() {
		return dataValue;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setDataValue(String newDataValue) {
		String oldDataValue = dataValue;
		dataValue = newDataValue;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, EcoreXESPackage.EVENT__DATA_VALUE, oldDataValue,
					dataValue));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EventType getEventType() {
		return eventType;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setEventType(EventType newEventType) {
		EventType oldEventType = eventType;
		eventType = newEventType == null ? EVENT_TYPE_EDEFAULT : newEventType;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, EcoreXESPackage.EVENT__EVENT_TYPE, oldEventType,
					eventType));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public Object eGet(int featureID, boolean resolve, boolean coreType) {
		switch (featureID) {
		case EcoreXESPackage.EVENT__SET:
			return isSet();
		case EcoreXESPackage.EVENT__TIMESTAMP:
			return getTimestamp();
		case EcoreXESPackage.EVENT__FATURE_AND_CLASS:
			if (resolve)
				return getFatureAndClass();
			return basicGetFatureAndClass();
		case EcoreXESPackage.EVENT__ID:
			if (resolve)
				return getId();
			return basicGetId();
		case EcoreXESPackage.EVENT__REFERENCEVALUE:
			if (resolve)
				return getReferencevalue();
			return basicGetReferencevalue();
		case EcoreXESPackage.EVENT__DATA_VALUE:
			return getDataValue();
		case EcoreXESPackage.EVENT__EVENT_TYPE:
			return getEventType();
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
		case EcoreXESPackage.EVENT__SET:
			setSet((Boolean) newValue);
			return;
		case EcoreXESPackage.EVENT__TIMESTAMP:
			setTimestamp((Date) newValue);
			return;
		case EcoreXESPackage.EVENT__FATURE_AND_CLASS:
			setFatureAndClass((FeatureAndClass) newValue);
			return;
		case EcoreXESPackage.EVENT__ID:
			setId((ID) newValue);
			return;
		case EcoreXESPackage.EVENT__REFERENCEVALUE:
			setReferencevalue((ReferenceValue) newValue);
			return;
		case EcoreXESPackage.EVENT__DATA_VALUE:
			setDataValue((String) newValue);
			return;
		case EcoreXESPackage.EVENT__EVENT_TYPE:
			setEventType((EventType) newValue);
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
		case EcoreXESPackage.EVENT__SET:
			setSet(SET_EDEFAULT);
			return;
		case EcoreXESPackage.EVENT__TIMESTAMP:
			setTimestamp(TIMESTAMP_EDEFAULT);
			return;
		case EcoreXESPackage.EVENT__FATURE_AND_CLASS:
			setFatureAndClass((FeatureAndClass) null);
			return;
		case EcoreXESPackage.EVENT__ID:
			setId((ID) null);
			return;
		case EcoreXESPackage.EVENT__REFERENCEVALUE:
			setReferencevalue((ReferenceValue) null);
			return;
		case EcoreXESPackage.EVENT__DATA_VALUE:
			setDataValue(DATA_VALUE_EDEFAULT);
			return;
		case EcoreXESPackage.EVENT__EVENT_TYPE:
			setEventType(EVENT_TYPE_EDEFAULT);
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
		case EcoreXESPackage.EVENT__SET:
			return set != SET_EDEFAULT;
		case EcoreXESPackage.EVENT__TIMESTAMP:
			return TIMESTAMP_EDEFAULT == null ? timestamp != null : !TIMESTAMP_EDEFAULT.equals(timestamp);
		case EcoreXESPackage.EVENT__FATURE_AND_CLASS:
			return fatureAndClass != null;
		case EcoreXESPackage.EVENT__ID:
			return id != null;
		case EcoreXESPackage.EVENT__REFERENCEVALUE:
			return referencevalue != null;
		case EcoreXESPackage.EVENT__DATA_VALUE:
			return DATA_VALUE_EDEFAULT == null ? dataValue != null : !DATA_VALUE_EDEFAULT.equals(dataValue);
		case EcoreXESPackage.EVENT__EVENT_TYPE:
			return eventType != EVENT_TYPE_EDEFAULT;
		}
		return super.eIsSet(featureID);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public String toString() {
		if (eIsProxy())
			return super.toString();

		StringBuilder result = new StringBuilder(super.toString());
		result.append(" (set: ");
		result.append(set);
		result.append(", timestamp: ");
		result.append(timestamp);
		result.append(", dataValue: ");
		result.append(dataValue);
		result.append(", eventType: ");
		result.append(eventType);
		result.append(')');
		return result.toString();
	}

} //EventImpl
