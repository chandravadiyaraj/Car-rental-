import React, { useState } from 'react';
import { View, TextInput, Button, Alert } from 'react-native';
import SQLite from 'react-native-sqlite-storage';

const db = SQLite.openDatabase({ name: 'fitnessTracker.db' });

const LogActivity = () => {
  const [activityType, setActivityType] = useState('');
  const [duration, setDuration] = useState('');
  const [calories, setCalories] = useState('');

  const logActivity = () => {
    db.transaction(tx => {
      tx.executeSql(
        'INSERT INTO activities (type, duration, calories) VALUES (?, ?, ?)',
        [activityType, duration, calories],
        (tx, results) => {
          Alert.alert('Activity logged successfully!');
        },
        (tx, error) => {
          Alert.alert('Error logging activity:', error.message);
        }
      );
    });
  };

  return (
    <View>
      <TextInput placeholder="Activity Type" onChangeText={setActivityType} />
      <TextInput placeholder="Duration (minutes)" onChangeText={setDuration} keyboardType="numeric" />
      <TextInput placeholder="Calories Burned" onChangeText={setCalories} keyboardType="numeric" />
      <Button title="Log Activity" onPress={logActivity} />
    </View>
  );
};

